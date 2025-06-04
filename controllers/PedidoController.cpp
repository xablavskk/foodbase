#include "PedidoController.hpp"

//construtor do controller
PedidoController::PedidoController() : service(db) {}


//metodo que salva pedido
Pedido PedidoController::salvarPedido(const Pedido& pedido, const Pagamento& pagamento) const {
    return service.salvarPedido(pedido, pagamento);
}

//metodo que busca pedido
Pedido PedidoController::buscarPedidoPorCd(int cdPedido) const {
    return service.buscarPedidoPorCd(cdPedido);
}
