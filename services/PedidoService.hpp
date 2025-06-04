#pragma once

#include <string>
#include "Pedido.hpp"
#include "../db/Database.hpp"
#include "PagamentoService.hpp"

class PagamentoService;

class PedidoService {
private:
    Database& db;
    PagamentoService& serviceP;

public:
    PedidoService(Database& dbRef, PagamentoService& pagamentoService);

    Pedido salvarPedido(Pedido& pedido, const Pagamento& pagamento) const;
    Pedido buscarPedidoPorCd(int cdPedido) const;
};
