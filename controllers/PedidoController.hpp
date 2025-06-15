#pragma once

#include "../models/Pedido.hpp"
#include "../models/Pagamento.hpp"
#include "../services/PedidoService.hpp"
#include "../db/Database.hpp"
#include "../services/PagamentoService.hpp"

class PedidoController {
private:
    Database db;
    PedidoService service;

public:
    PedidoController();
    Pedido salvarPedido(Pedido &pedido) const;
    Pedido atualizarPedido(Pedido &pedido) const;
    Pedido buscarPedidoPorCd(int cdPedido) const;
};
