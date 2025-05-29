//
// Created by mario on 26/05/2025.
//

#pragma once
#include <iostream>

enum class TipoPagamentoEnum {
    PIX, DINHEIRO_FISICO, CARTAO_DEBITO, CARTAO_CREDITO
};

inline char toChar(TipoPagamentoEnum tipo) {
    switch (tipo) {
        case TipoPagamentoEnum::PIX: return 'P';
        case TipoPagamentoEnum::DINHEIRO_FISICO: return 'F';
        case TipoPagamentoEnum::CARTAO_DEBITO: return 'D';
        case TipoPagamentoEnum::CARTAO_CREDITO: return 'C';
        default: return 'P';
    }
}

inline TipoPagamentoEnum toEnum(char c) {
    switch (c) {
        case 'P': return TipoPagamentoEnum::PIX;
        case 'F': return TipoPagamentoEnum::DINHEIRO_FISICO;
        case 'D': return TipoPagamentoEnum::CARTAO_DEBITO;
        case 'C': return TipoPagamentoEnum::CARTAO_CREDITO;
        default:
            throw std::invalid_argument("Tipo de pagamento inválido: " + std::string(1, c));
    }
}
