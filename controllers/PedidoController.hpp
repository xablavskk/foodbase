#pragma once

#include "../models/Pedido.hpp"
#include "../services/PedidoService.hpp"
#include "../db/Database.hpp"

class PedidoController {
private:
    Database db;
    PedidoService service;

public:
    PedidoController();
    Pedido salvarPedido(const Pedido& pedido) const{
        return service.salvarPedido(pedido);
    };

    Pedido buscarPedidoPorCd(int cd_pedido) const{
        return service.buscarPedidoPorCd(cd_pedido);
    };

};
