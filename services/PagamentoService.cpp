// uma alternativa tradicional do #ifndef HEADER_H | #define HEADER_H e #endif
#pragma once

// imports das bibliotecas e classes para uso e desenvolvimento na regra de negocio
#include "PagamentoService.hpp"
#include <iostream>

// contrutor da classe PagamentoService recebendo o banco como injecao de dependencia - para inicializacao do banco e execucao de query's
PagamentoService::PagamentoService(Database& dbRef) : db(dbRef) {}

// metodo para salvar uma entidade, no caso, Pagamento -- recebemos um ponteido da classe Pagamento, para controlar o tempo de vida do objeto
Pagamento PagamentoService::salvarPagamento(const Pagamento& pagamento) const {
    if (std::isblank(toChar(pagamento.getTpPagamento()))) {
        throw std::invalid_argument("Nome do pagamento não pode ser vazio.");
    }

    // stringstream para executar a query no banco

    std::stringstream ss;
    ss << "INSERT INTO pagamento (tp_pagamento, vl_pagamento) VALUES ('"<< toChar(pagamento.getTpPagamento()) << "', " << pagamento.getVlPagamento() << ") RETURNING cd_pagamento, tp_pagamento, vl_pagamento;";

    std::cout << ss.str() << std::endl;
    std::cout << "INSERIU OS DADOS\n" << std::endl;

    // resultado da query e execucao pelo service db
    // chamada do metodo executarQuery do servico db
    auto result = db.executarQuery(ss.str());

    // se a query nao tiver um retorno, lanca um runtime
    if (result.empty()) {
        throw std::runtime_error("Erro ao salvar pagamento: resultado vazio.");
    }

    // com o reotrno da query, mapeamos os results para recebermos os atributos obtidos das colunas do banco.
    // o result é uma matriz de valores, armazenando linhas e colunas
    // result[0] é pego o primeiro resultado obtido juntamnete ao resultado da coluna cd_pagamento por exemplo -> result[0]["cd_pagamento"] do tipo inteiro .as<int>

    int codigoPagamento = result[0]["cd_pagamento"].as<int>();

    double valorPagamento = result[0]["vl_pagamento"].as<double>();

    std::cout << codigoPagamento << std::endl;
    std::cout << valorPagamento << std::endl;

    // temos o mapeamento de string no tipoPagamento pois trabalhamos com um enum no projeto. Ele é tido como string e depois é feito a conversao para o tipoEnum do TipoPagamentoEnum
    std::string tipoPagamentoStr = result[0]["tp_pagamento"].as<std::string>();

    std::cout << tipoPagamentoStr << std::endl;
    char tipoPagamento = tipoPagamentoStr.empty() ? '?' : tipoPagamentoStr[0];

    std::cout << "codigo: " << codigoPagamento << std::endl;
    std::cout << "tipo pagamento: " << tipoPagamento << std::endl;
    std::cout << "valor pago: " << valorPagamento << std::endl;

    TipoPagamentoEnum tipoEnum = toEnum(tipoPagamento);

    Pagamento pagamentoConstrutor(codigoPagamento, tipoEnum, valorPagamento);

    return pagamentoConstrutor;
}

// metodo para buscar um unico pagamento, que tambem, retorna um objeto pagamento
Pagamento PagamentoService::buscarPagamentoPorId(int id) const {
    // é lido como parametro um id para podemos fazer a consulta no banco de dados, se tiver vazio é por que nao existe no banco ou se for zero é invalido
    if (id == 0) {
        throw std::invalid_argument("Id inválido.");
    }

    // stringstream para realizarmos a query com select + where id
    std::stringstream ss;
    ss << "SELECT * FROM pagamento WHERE cd_pagamento = " << id << ";";

    // resultado da query e execucao pelo service db
    // chamada do metodo executarQuery do servico db
    auto result = db.executarQuery(ss.str());

    // se a query nao tiver um retorno, lanca um runtime
    if (result.empty()) {
        throw std::runtime_error("Erro ao buscar pagamento: resultado vazio.");
    }

    // com o reotrno da query, mapeamos os results para recebermos os atributos obtidos das colunas do banco.
    // o result é uma matriz de valores, armazenando linhas e colunas
    // result[0] é pego o primeiro resultado obtido juntamnete ao resultado da coluna cd_pagamento por exemplo -> result[0]["cd_pagamento"] do tipo inteiro .as<int>

    int codigoPagamento = result[0]["cd_pagamento"].as<int>();

    // temos o mapeamento de string no tipoPagamento pois trabalhamos com um enum no projeto. Ele é tido como string e depois é feito a conversao para o tipoEnum do TipoPagamentoEnum
    std::string tipoPagamentoStr = result[0]["tp_pagamento"].as<std::string>();
    char tipoPagamento = tipoPagamentoStr.empty() ? '?' : tipoPagamentoStr[0];
    double valorPagamento = result[0]["vl_pagamento"].as<double>();

    std::cout << "codigo: " << codigoPagamento << std::endl;
    std::cout << "tipo pagamento: " << tipoPagamento << std::endl;
    std::cout << "valor pago: " << valorPagamento << std::endl;

    TipoPagamentoEnum tipoEnum = toEnum(tipoPagamento);

    Pagamento pagamento(codigoPagamento, tipoEnum, valorPagamento);
    return pagamento;
}

// metodo que busca todos os pagamentos no banco de dados
std::vector<Pagamento> PagamentoService::buscarTodosPagamentos() const {
    // vetor onde os pagamentos serão armazenados
    std::vector<Pagamento> pagamentos;

    // monta a query sql para buscar código e tipo de pagamento
    std::stringstream ss;
    ss << "SELECT cd_pagamento, tp_pagamento FROM pagamento;";

    // resultado da query e execucao pelo service db
    // chamada do metodo executarQuery do servico db
    auto result = db.executarQuery(ss.str());

    // Itera sobre cada linha do resultado
    for (const auto& row : result) {
        // leitura do código do pagamento (inteiro)
        int cdPagamento = row["cd_pagamento"].as<int>();

        // leitura do tipo de pagamento (string)
        std::string tipo = row["tp_pagamento"].as<std::string>();

        // Pega o primeiro caractere da string ou usa '?' se estiver vazia
        char tipoPagamento = tipo.empty() ? '?' : tipo[0];

        // Converte o caractere em um valor do enum TipoPagamentoEnum
        TipoPagamentoEnum tipoEnum = toEnum(tipoPagamento);

        // Cria e adiciona o objeto Pagamento ao vetor, construindo diretamente no local
        pagamentos.emplace_back(cdPagamento, tipoEnum);
    }

    // Retorna o vetor com todos os pagamentos encontrados
    return pagamentos;
}
