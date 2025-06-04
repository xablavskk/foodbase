#pragma once

#include "../models/Pedido.hpp"
#include "../models/Pagamento.hpp"
#include "../services/PedidoService.hpp"
#include "../db/Database.hpp"

class PedidoController {
private:
    Database db;
    PedidoService service;

public:
    PedidoController();
    Pedido salvarPedido(const Pedido& pedido, const Pagamento& pagamento) const{
        return service.salvarPedido(pedido, pagamento);
    };

    Pedido buscarPedidoPorCd(int cdPedido) const{
        return service.buscarPedidoPorCd(cdPedido);
    };

};
