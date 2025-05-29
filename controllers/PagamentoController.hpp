#pragma once

#include "../models/Pagamento.hpp"
#include "../services/PagamentoService.hpp"
#include "../db/Database.hpp"

class PagamentoController {
private:
    Database db;
    PagamentoService service;

public:
    PagamentoController();
    Pagamento salvarPagamento(const Pagamento& pagamento) const;
    Pagamento buscarPagamentoPorId(int id) const;

    std::vector<Pagamento> buscarTodosPagamentos() const;
};