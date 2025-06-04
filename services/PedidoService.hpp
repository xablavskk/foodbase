#pragma once
#include <string>

#include "Pedido.hpp"
#include "../db/Database.hpp"

class PedidoService {
private:
    Database& db;

public:
    PedidoService(Database& dbRef);
    Pedido salvarPedido(const Pedido& pedido, const Pagamento& pagamento) const;
    Pedido buscarPedidoPorCd(int cdPedido) const;
};
