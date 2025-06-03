#pragma once // evita inclusao multiplas do header durante a compilacao

#include "../models/Pagamento.hpp"       // inclui a definicao da classe pagamento
#include "../services/PagamentoService.hpp" // inclui a logica de negocio relacionada a pagamento
#include "../db/Database.hpp"            // inclui a classe de acesso ao banco de dados

// define a classe que atua como controlador de pagamento
class PagamentoController {
private:
    Database db;     // instancia local para conexao com o banco de dados
    PagamentoService service; // instancia do servico que contem a logica de negocio dos pagamentos

public:
    PagamentoController(); // construtor padrao do controlador
    Pagamento salvarPagamento(const Pagamento& pagamento) const; // metodo para salvar um pagamento
    Pagamento buscarPagamentoPorId(int id) const; // metodo para buscar um pagamento pelo id

    std::vector<Pagamento> buscarTodosPagamentos() const; // metodo para retornar todos os pagamentos
};
