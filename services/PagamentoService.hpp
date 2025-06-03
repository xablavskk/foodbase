#pragma once

#include "Pagamento.hpp"
#include "../db/Database.hpp"

class PagamentoService {
private:
    Database& db;

public:
    PagamentoService(Database& dbRef);
    Pagamento salvarPagamento(const Pagamento& pagamento) const;
    Pagamento buscarPagamentoPorId(int id) const;
    std::vector<Pagamento> buscarTodosPagamentos() const;

};