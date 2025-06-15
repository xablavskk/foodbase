#pragma once

#include <string>
#include "Pedido.hpp"
#include "../db/Database.hpp"
#include "PagamentoService.hpp"

class PagamentoService;

class PedidoService {
private:
    Database& db;

public:
    PedidoService(Database& dbRef);

    Pedido salvarPedido(Pedido &pedido) const;
    Pedido atualizarPedido(const Pedido &pedido) const;
    Pedido buscarPedidoPorCd(int cdPedido) const;
};
