#include "PedidoController.hpp"

//construtor do controller
PedidoController::PedidoController() : service(db) {}


//metodo que salva pedido
Pedido PedidoController::salvarPedido(const Pedido& pedido) const {
    return service.salvarPedido(pedido);
}

//metodo que busca pedido
Pedido PedidoController::buscarPedidoPorCd(int cd_pedido) const {
    return service.buscarPedidoPorCd(cd_pedido);
}
