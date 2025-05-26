#include "PedidoController.hpp"

PedidoController::PedidoController() : service(db) {}

Pedido PedidoController::salvarPedido(const Pedido& pedido) const {
    return service.salvarPedido(pedido);
}

Pedido PedidoController::buscarPedidoPorId(int id) const {
    return service.buscarPedidoPorId(id);
}
