//
// Created by mario on 26/05/2025.
//

#pragma once

enum class TipoPagamentoEnum {
    PIX, DINHEIRO_FISICO, CARTAO_DEBITO, CARTAO_CREDITO
};

inline char toChar(TipoPagamentoEnum tipo) {
    switch (tipo) {
        case TipoPagamentoEnum::PIX: return 'P';
        case TipoPagamentoEnum::DINHEIRO_FISICO: return 'F';
        case TipoPagamentoEnum::CARTAO_DEBITO: return 'D';
        case TipoPagamentoEnum::CARTAO_CREDITO: return 'C';
        default: return 'z';
    }
}