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
    PagamentoService pagamentoService;

public:
    PedidoController();
    Pedido salvarPedido(Pedido &pedido, Pagamento &pagamento) const;/* isso ta errado{
        return service.salvarPedido(pedido, pagamento); 
    };*/

    Pedido buscarPedidoPorCd(int cdPedido) const;/*{
        return service.buscarPedidoPorCd(cdPedido);
    };*/
};
