#pragma once // evita inclusao multipla do header

#include <iostream> // necessario para std::invalid_argument e std::string

// definicao do enum para representar os tipos de pagamento
enum class TipoPagamentoEnum {
    PIX,
    DINHEIRO_FISICO,
    CARTAO_DEBITO,
    CARTAO_CREDITO
};

// funcao que converte o enum para caractere correspondente
inline char toChar(TipoPagamentoEnum tipo) {
    switch (tipo) {
        case TipoPagamentoEnum::PIX: return 'P';
        case TipoPagamentoEnum::DINHEIRO_FISICO: return 'F';
        case TipoPagamentoEnum::CARTAO_DEBITO: return 'D';
        case TipoPagamentoEnum::CARTAO_CREDITO: return 'C';
        default: return 'P'; // valor padrao em caso de tipo nao reconhecido
    }
}

// funcao que converte um caractere em um valor do enum
inline TipoPagamentoEnum toEnum(char c) {
    switch (c) {
        case 'P': return TipoPagamentoEnum::PIX;
        case 'F': return TipoPagamentoEnum::DINHEIRO_FISICO;
        case 'D': return TipoPagamentoEnum::CARTAO_DEBITO;
        case 'C': return TipoPagamentoEnum::CARTAO_CREDITO;
        default:
            // lanca excecao se caractere for invalido
            throw std::invalid_argument("Tipo de pagamento invalido: " + std::string(1, c));
    }
}
