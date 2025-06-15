#include "PedidoController.hpp"

//construtor do controller
PedidoController::PedidoController()
    : service(db)
{}

//metodo que salva pedido
Pedido PedidoController::salvarPedido(Pedido &pedido) const { //, const Pagamento& pagamento
    return service.salvarPedido(pedido);
}

//metodo que atualiza um pedido
Pedido PedidoController::atualizarPedido(Pedido &pedido) const {
    return service.atualizarPedido(pedido);
}


//metodo que busca pedido
Pedido PedidoController::buscarPedidoPorCd(int cdPedido) const {
    return service.buscarPedidoPorCd(cdPedido);
}
