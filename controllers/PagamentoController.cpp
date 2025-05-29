#include "PagamentoController.hpp"
#include <iostream>

PagamentoController::PagamentoController() : service(db) {}

Pagamento PagamentoController::salvarPagamento(const Pagamento& pagamento) const {
    return service.salvarPagamento(pagamento);
}

Pagamento PagamentoController::buscarPagamentoPorId(int id) const {
    return service.buscarPagamentoPorId(id);
}

std::vector<Pagamento> PagamentoController::buscarTodosPagamentos() const {
    return service.buscarTodosPagamentos();
}