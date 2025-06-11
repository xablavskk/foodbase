#include "PedidoService.hpp"

#include <iostream>
#pragma once

PedidoService::PedidoService(Database& dbRef) : db(dbRef) {}

Pedido PedidoService::salvarPedido(const Pedido& pedido) const {
    if (pedido.getName().empty()) {
        throw std::invalid_argument("Nome do pedido não pode ser vazio.");
    }

    std::stringstream ss;
    ss << "INSERT INTO pedido (cd_pedido, st_pedido) VALUES ("<< pedido.getId() << ", '" << pedido.getName() << "') RETURNING cd_pedido;";

    auto result = db.executarQuery(ss.str());

    if (result.empty()) {
        throw std::runtime_error("Erro ao salvar pedido: resultado vazio.");
    }

    return pedido;
}

Pedido PedidoService::buscarPedidoPorId(int id) const {
    if (id == 0) {
        throw std::invalid_argument("Id inválido.");
    }

    std::stringstream ss;
    ss << "SELECT * FROM pedidos WHERE id = " << id << ";";

    auto result = db.executarQuery(ss.str());

    if (result.empty()) {
        throw std::runtime_error("Erro ao buscar pedido: resultado vazio.");
    }

    int pedidoId = result[0]["id"].as<int>();
    std::string nome = result[0]["nome"].as<std::string>();

    std::cout<<"id"<<pedidoId;
    std::cout<<"nome"<<nome;

    Pedido pedido(pedidoId, nome);

    return pedido;
}


