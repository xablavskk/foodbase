#pragma once
#include "PagamentoService.hpp"
#include <iostream>

PagamentoService::PagamentoService(Database& dbRef) : db(dbRef) {}

Pagamento PagamentoService::salvarPagamento(const Pagamento& pagamento) const {
    if (std::isblank(toChar(pagamento.getTpPagamento()))) {
        throw std::invalid_argument("Nome do pagamento não pode ser vazio.");
    }

    std::stringstream ss;
    ss << "INSERT INTO pagamento (cd_pagamento, tp_pagamento, vl_pagamento) VALUES ("<< pagamento.getCdPagamento() << ", '" << toChar(pagamento.getTpPagamento()) << ", '" << pagamento.getVlPagamento() << "') RETURNING id;";

    auto result = db.executarQuery(ss.str());

    if (result.empty()) {
        throw std::runtime_error("Erro ao salvar pagamento: resultado vazio.");
    }

    return pagamento;
}

Pagamento PagamentoService::buscarPagamentoPorId(int id) const {
    if (id == 0) {
        throw std::invalid_argument("Id inválido.");
    }

    std::stringstream ss;
    ss << "SELECT * FROM pagamento WHERE cd_pagamento = " << id << ";";

    auto result = db.executarQuery(ss.str());

    if (result.empty()) {
        throw std::runtime_error("Erro ao buscar pagamento: resultado vazio.");
    }

    int codigoPagamento = result[0]["cd_pagamento"].as<int>();
    std::string tipoPagamentoStr = result[0]["tp_pagamento"].as<std::string>();
    char tipoPagamento = tipoPagamentoStr.empty() ? '?' : tipoPagamentoStr[0];
    float valorPagamento = result[0]["vl_pagamento"].as<float>();

    std::cout << "codigo: " << codigoPagamento << std::endl;
    std::cout << "tipo pagamento: " << tipoPagamento << std::endl;
    std::cout << "valor pago: " << valorPagamento << std::endl;

    TipoPagamentoEnum tipoEnum = toEnum(tipoPagamento);

    Pagamento pagamento(codigoPagamento, tipoEnum, valorPagamento);
    return pagamento;
}

std::vector<Pagamento> PagamentoService::buscarTodosPagamentos() const {
    std::vector<Pagamento> pagamentos;

    std::stringstream ss;
    ss << "SELECT cd_pagamento, tp_pagamento FROM pagamento;";

    auto result = db.executarQuery(ss.str());

    for (const auto& row : result) {
        int cdPagamento = row["cd_pagamento"].as<int>();

        std::string tipo = row["tp_pagamento"].as<std::string>();
        char tipoPagamento = tipo.empty() ? '?' : tipo[0];

        TipoPagamentoEnum tipoEnum = toEnum(tipoPagamento);

        pagamentos.emplace_back(cdPagamento, tipoEnum);
    }

    return pagamentos;
}