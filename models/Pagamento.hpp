//
// Created by mario on 26/05/2025.
//

#pragma once
#include "../enums/TipoPagamentoEnum.hpp"


class Pagamento {
private:
    int cdPagamento;
    TipoPagamentoEnum tpPagamento;
    float qtValorPago;

public:
    Pagamento();
    Pagamento(int cd_pagamento);
    Pagamento(int cd_pagamento, TipoPagamentoEnum tipo_pagamento, float qt_valor_pago);

    [[nodiscard]] int getCdPagamento() const;
    [[nodiscard]] TipoPagamentoEnum getTpPagamento() const;
    [[nodiscard]] float getQtValorPago() const;

    void setCdPagamento(int cd_pagamento);
    void setTpPagamento(TipoPagamentoEnum tipo_pagamento);
    void setQtValorPago(float qt_valor_pago);
};
