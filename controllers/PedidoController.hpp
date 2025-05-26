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
    Pedido salvarPedido(const Pedido& pedido) const;
    Pedido buscarPedidoPorId(int id) const;
};
