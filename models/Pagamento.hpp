//
// Created by mario on 26/05/2025.
//

#pragma once
#include "../enums/TipoPagamentoEnum.hpp"


class Pagamento {
private:
    int cdPagamento;
    TipoPagamentoEnum tpPagamento;
    double vlPagamento;

public:
    Pagamento();
    Pagamento(int cdPagamento);
    Pagamento(int cdPagamento, TipoPagamentoEnum tpPagamento);
    Pagamento(TipoPagamentoEnum tpPagamento, double vlPagamento);
    Pagamento(int cdPagamento, TipoPagamentoEnum tpPagamento, double vlPagamento);

    [[nodiscard]] int getCdPagamento() const;
    [[nodiscard]] TipoPagamentoEnum getTpPagamento() const;
    [[nodiscard]] double getVlPagamento() const;

    void setCdPagamento(int cd_pagamento);
    void setTpPagamento(TipoPagamentoEnum tpPagamento);
    void setVlPagamento(double vlPagamento);
};
