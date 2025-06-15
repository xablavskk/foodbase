#include "PedidoService.hpp"
#include "Produto.hpp"
#include "Pagamento.hpp"

#include <iostream>
#pragma once

PedidoService::PedidoService(Database& dbRef) : db(dbRef) {}


//Salvar pedidos
Pedido PedidoService::salvarPedido(Pedido &pedido) const {
    if (pedido.getStPedido().empty()) {
        throw std::invalid_argument("O pedido precisa ter um status.");
    }

    std::stringstream ss;
    ss << "INSERT INTO pedido (pagamento_cd_pagamento, produto_cd_produto, st_pedido) VALUES (" << pedido.getPagamento()->getCdPagamento() << ", " << pedido.getProduto()->getCdProduto() << ", '" << pedido.getStPedido() << "') RETURNING cd_pedido, st_pedido;";
    
    auto result = db.executarQuery(ss.str());

    if (result.empty()) {
        throw std::runtime_error("Erro ao salvar pedido: resultado vazio.");
    }

    int cdPedido = result[0]["cd_pedido"].as<int>();
    std::string stPedido = result[0]["st_pedido"].as<std::string>();

    Pedido pedidoRetorno(cdPedido, pedido.getPagamento(), 0, stPedido);
    return pedidoRetorno;
}

Pedido PedidoService::atualizarPedido(const Pedido& pedido) const {
    if (pedido.getCdPedido() == 0) {
        throw std::invalid_argument("ID do pedido inválido.");
    }

    try {
        pqxx::work txn(*db.getConnection());  // inicau ma transacao explicita

        TipoPagamentoEnum tpPagamento = pedido.getPagamento()->getTpPagamento();
        std::string tipoPagamentoStr(1, toChar(tpPagamento));

        // atualzia status do pedido
        txn.exec0("UPDATE pedido SET st_pedido = " +
                  txn.quote(pedido.getStPedido()) +
                  " WHERE cd_pedido = " + txn.quote(pedido.getCdPedido()));

        // atualiza pagamento
        txn.exec0("UPDATE pagamento SET "
                  "vl_pagamento = " + txn.quote(pedido.getPagamento()->getVlPagamento()) + ", "
                  "tp_pagamento = " + txn.quote(tipoPagamentoStr) +
                  " WHERE cd_pagamento = " + txn.quote(pedido.getPagamento()->getCdPagamento()));

        txn.commit(); // salva, caso de erro é dado um rollback nessa sequencia de comandos
        std::cout << "[INFO] Pedido e dependências atualizados com sucesso." << std::endl;

        return buscarPedidoPorCd(pedido.getCdPedido());

    } catch (const std::exception& e) {
        std::cerr << "[ERRO] Falha ao atualizar pedido: " << e.what() << std::endl;
        throw;
    }
}

Pedido PedidoService::buscarPedidoPorCd(int cdPedido) const {
    if (cdPedido == 0) {
        throw std::invalid_argument("Codigo inválido.");
    }

    std::stringstream ss;
    ss << "SELECT "
       << "pe.cd_pedido, "
       << "pe.st_pedido, "
       << "pa.cd_pagamento, "
       << "pa.vl_pagamento, "
       << "pa.tp_pagamento, "
       << "pr.cd_produto, "
       << "pr.nm_produto, "
       << "pr.ds_produto, "
       << "pr.vl_produto, "
       << "pr.st_produto "
       << "FROM pedido pe "
       << "JOIN pagamento pa ON pe.pagamento_cd_pagamento = pa.cd_pagamento "
       << "JOIN produto pr ON pe.produto_cd_produto = pr.cd_produto "
       << "WHERE pe.cd_pedido = " << cdPedido << ";";

    auto result = db.executarQuery(ss.str());

    if (result.empty()) {
        throw std::runtime_error("Erro ao buscar pedido: resultado vazio.");
    }

    int cdPedidoResult = result[0]["cd_pedido"].as<int>();
    std::string stPedido = result[0]["st_pedido"].as<std::string>();

    int cdPagamento = result[0]["cd_pagamento"].as<int>();
    double vlPagamento = result[0]["vl_pagamento"].as<double>();
    std::string tipoPagamentoStr = result[0]["tp_pagamento"].as<std::string>();
    char tipoPagamento = tipoPagamentoStr.empty() ? '?' : tipoPagamentoStr[0];

    int cdProduto = result[0]["cd_produto"].as<int>();
    double vlProduto = result[0]["vl_produto"].as<double>();
    std::string dsProduto = result[0]["ds_produto"].as<std::string>();
    std::string nmProduto = result[0]["nm_produto"].as<std::string>();
    std::string stProduto = result[0]["st_produto"].as<std::string>();

    Pagamento* pagamento = new Pagamento(cdPagamento, toEnum(tipoPagamento), vlPagamento);

    Produto* produto = new Produto(cdProduto, nmProduto, dsProduto, vlProduto, stProduto);

    std::cout << "Codigo do Pedido: " << cdPedidoResult << std::endl;
    std::cout << "Status do Pedido: " << stPedido << std::endl;
    std::cout << "Codigo do Pagamento: " << cdPagamento << ", Valor: " << vlPagamento << ", Tipo do Pagamento: " <<
            toChar(pagamento->getTpPagamento()) << std::endl;

    std::cout << "Codigo do Produto: " << cdProduto << ", Descrição: " << dsProduto << ", Nome do Produto: " << nmProduto << ", Status do Produto" << stProduto << std::endl;

    Pedido pedido(cdPedidoResult, pagamento, produto, stPedido);

    return pedido;
}

/*SELECT 
    pe.cd_pedido, 
    pe.st_pedido, 
    pa.cd_pagamento, 
    pa.vl_pagamento, 
    pr.cd_produto, 
    pr.ds_produto 
FROM 
    pedido pe 
JOIN 
    pagamento pa 
    ON pe.cd_pagamento = pa.cd_pagamento 
JOIN 
    produto pr 
    ON pe.cd_produto = pr.cd_produto where pe.cd_pedido = 2;*/


