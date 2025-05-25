#include "PedidoController.hpp"

#include <iostream>
#include <sstream>

using namespace std;

Pedido PedidoController::salvarPedido(const Pedido& pedido) const {
    std::stringstream ss;

    cout << pedido.getName() << endl;
    cout << pedido.getId() << endl;

    ss << "INSERT INTO pedidos (id, nome) VALUES (" << pedido.getId() << ", '" << pedido.getName() << "') RETURNING id;";

    cout << ss.str() << endl;

    if (auto result = db.executarQuery(ss.str()); result.empty()) {
        throw std::runtime_error("Erro ao salvar pedido: resultado vazio.");
    }

    return pedido;
}

Pedido PedidoController::buscarPedidoPorId(int id) const {
    std::stringstream ss;
    ss << "SELECT id, nome FROM pedidos WHERE id = " << id << ";";
    auto result = db.executarQuery(ss.str());

    if (!result.empty()) {
        return Pedido(result[0]["id"].as<int>(), result[0]["nome"].as<std::string>());
    }
    return Pedido(-1, "");
}
