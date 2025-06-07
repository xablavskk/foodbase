#include "PedidoService.hpp"
#include "PagamentoService.hpp"
#include <iostream>
#pragma once

PedidoService::PedidoService(Database& dbRef, PagamentoService& pagamentoService) : db(dbRef), serviceP(pagamentoService) {}


//Salvar pedidos
Pedido PedidoService::salvarPedido(Pedido &pedido, Pagamento &pagamento) const {
    if (pedido.getStPedido() == "") {
        throw std::invalid_argument("O pedido precisa ter um status.");
    }

    pedido.setPagamento(&pagamento);

    std::stringstream ss;
    ss << "INSERT INTO pedido (pagamento_cd_pagamento, st_pedido) VALUES (" << pedido.getPagamento()->getCdPagamento() << ", '" << pedido.getStPedido() << "') RETURNING cd_pedido, st_pedido;";
    
    auto result = db.executarQuery(ss.str());

    if (result.empty()) {
        throw std::runtime_error("Erro ao salvar pedido: resultado vazio.");
    }

    int cdPedido = result[0]["cd_pedido"].as<int>();
    std::string stPedido = result[0]["st_pedido"].as<std::string>();

    Pedido pedidoRetorno(cdPedido, pedido.getPagamento(), 0, stPedido);
    return pedidoRetorno;
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
       << "pa.tp_pagamento "
       // << "pr.cd_produto, "
       // << "pr.ds_produto "
       << "FROM pedido pe "
       << "JOIN pagamento pa ON pe.pagamento_cd_pagamento = pa.cd_pagamento "
       // << "JOIN produto pr ON pe.cd_produto = pr.cd_produto "
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

    // int cdProduto = result[0]["cd_produto"].as<int>();
    // std::string dsProduto = result[0]["ds_produto"].as<std::string>();

    Pagamento* pagamento = new Pagamento(cdPagamento, toEnum(tipoPagamento), vlPagamento);

    std::cout << "Codigo do Pedido: " << cdPedidoResult << std::endl;
    std::cout << "Status do Pedido: " << stPedido << std::endl;
    std::cout << "Codigo do Pagamento: " << cdPagamento << ", Valor: " << vlPagamento << ", Tipo do Pagamento: " <<
            toChar(pagamento->getTpPagamento()) << std::endl;

    // std::cout << "Codigo do Produto: " << cdProduto << ", Descrição: " << dsProduto << std::endl;

    Pedido pedido(cdPedidoResult, pagamento, 02, stPedido);

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


