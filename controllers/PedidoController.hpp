#pragma once
#include "../models/Pedido.hpp"
#include "../db/Database.hpp"

class PedidoController {
private:
    Database db;

public:
    Pedido salvarPedido(const Pedido &pedido) const;
    Pedido buscarPedidoPorId(int id) const;
};