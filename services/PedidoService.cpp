#include "PedidoService.hpp"

#include <iostream>
#pragma once

PedidoService::PedidoService(Database& dbRef) : db(dbRef) {}


//Salvar pedidos
Pedido PedidoService::salvarPedido(const Pedido& pedido) const {
    if (pedido.getCdPedido() == 0) {
        throw std::invalid_argument("Campos Obrigatórios: Codigo do Pedido.");
    }

    std::stringstream ss;
    ss << "INSERT INTO pedido (cd_pedido, pagamento_cd_pagamento, produto_cd_produto, st_pedido) VALUES ("
    << pedido.getCdPedido() << ", "
    << pedido.getPagamento_cd_pagamento() << ", "
    << pedido.getProduto_cd_produto() << ", '"
    << pedido.getStPedido() << "') RETURNING cd_pedido;"; 
    
    //teste << pedido.getCdPagamento() << ", '" << pedido.getPagamento_cd_pagamento() << ",'" << pedido.getProduto_cd_produto() << ",'" << pedido.getStPedido() << "' 

    auto result = db.executarQuery(ss.str());

    if (result.empty()) {
        throw std::runtime_error("Erro ao salvar pedido: resultado vazio.");
    }

    return pedido;
}

Pedido PedidoService::buscarPedidoPorCd(int cd_pedido) const {
    if (cd_pedido == 0) {
        throw std::invalid_argument("Codigo inválido.");
    }

    std::stringstream ss;
    ss << "SELECT * FROM pedido WHERE cd_pedido = " << cd_pedido << ";";

    auto result = db.executarQuery(ss.str());

    if (result.empty()) {
        throw std::runtime_error("Erro ao buscar pedido: resultado vazio.");
    }

    int pedidoId = result[0]["id"].as<int>();
    std::string nome = result[0]["nome"].as<std::string>();

    std::cout<<"Codigo do Pedido"<< cd_pedido;
    std::cout<<"Codigo do Pagamento"<< pagamento_cd_pagamento;
    std::cout<<"Codigo do Produto"<< produto_cd_produto;
    std::cout<<"Status do Pedido"<< st_pedido;

    Pedido pedido(int cd_pedido, int pagamento_cd_pagamento, int produto_cd_produto, std::string st_pedido);

    return pedido;
}


