#include "PagamentoController.hpp" // inclui o header da classe pagamento controller

// construtor do pagamento controller inicializa o service com a instancia de db
PagamentoController::PagamentoController() : service(db) {}

// metodo que salva um pagamento delegando a chamada ao service
Pagamento PagamentoController::salvarPagamento(const Pagamento& pagamento) const {
    return service.salvarPagamento(pagamento);
}

// metodo que busca um pagamento pelo id delegando ao service
Pagamento PagamentoController::buscarPagamentoPorId(int id) const {
    return service.buscarPagamentoPorId(id);
}

// metodo que busca todos os pagamentos usando o service
std::vector<Pagamento> PagamentoController::buscarTodosPagamentos() const {
    return service.buscarTodosPagamentos();
}
