#include "PedidoService.hpp"
#include "PagamentoService.cpp"
#include <iostream>
#pragma once

PedidoService::PedidoService(Database& dbRef, PagamentoService& pagamentoService) : db(dbRef), serviceP(pagamentoService) {}


//Salvar pedidos
Pedido PedidoService::salvarPedido(const Pedido& pedido, const Pagamento& pagamento) const {
    if (pedido.getCdPedido() == 0) {
        throw std::invalid_argument("Campos Obrigatórios: Codigo do Pedido.");
    }

    Pagamento* pagamento = serviceP.salvarPagamento(&pagamento);

    pedido.setPagamento(&pagamento);

    std::stringstream ss;
    ss << "INSERT INTO pedido (pagamento_cd_pagamento, produto_cd_produto, st_pedido) VALUES ("
    << pedido.getPagamento().getCdPagamento() << ", "
    << pedido.getProduto() << ", '"
    << pedido.getStPedido() << "') RETURNING cd_pedido;"; 
    
    //teste << pedido.getCdPagamento() << ", '" << pedido.getpagamento() << ",'" << pedido.getProduto_cd_produto() << ",'" << pedido.getStPedido() << "' 

    auto result = db.executarQuery(ss.str());

    if (result.empty()) {
        throw std::runtime_error("Erro ao salvar pedido: resultado vazio.");
    }

    return pedido;
}

Pedido PedidoService::buscarPedidoPorCd(int cdPedido) const {
    if (cdPedido == 0) {
        throw std::invalid_argument("Codigo inválido.");
    }

    std::stringstream ss;
    ss << "SELECT * FROM pedido WHERE cdPedido = " << cdPedido << ";";

    auto result = db.executarQuery(ss.str());

    if (result.empty()) {
        throw std::runtime_error("Erro ao buscar pedido: resultado vazio.");
    }

    int pedidoId = result[0]["id"].as<int>();
    std::string nome = result[0]["nome"].as<std::string>();

    std::cout<<"Codigo do Pedido"<< cdPedido;
    std::cout<<"Codigo do Pagamento"<< pagamento;
    std::cout<<"Codigo do Produto"<< produto_cd_produto;
    std::cout<<"Status do Pedido"<< stPedido;

    Pedido pedido(int cdPedido, int pagamento, int produto_cd_produto, std::string stPedido);

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
    ON pe.cd_produto = pr.cd_produto where pe.cd_pedido = cd_pedido;*/


