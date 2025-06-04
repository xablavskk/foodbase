#include "PedidoController.hpp"

//construtor do controller
PedidoController::PedidoController()
    : db()
    , pagamentoService(db)
    , service(db, pagamentoService)
{}

//metodo que salva pedido
Pedido PedidoController::salvarPedido(Pedido& pedido, const Pagamento& pagamento) const { //, const Pagamento& pagamento
    return service.salvarPedido(pedido, pagamento);
}

//metodo que busca pedido
Pedido PedidoController::buscarPedidoPorCd(int cdPedido) const {
    return service.buscarPedidoPorCd(cdPedido);
}
