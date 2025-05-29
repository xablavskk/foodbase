
#include "Pagamento.hpp"

Pagamento::Pagamento(const int cdPagamento, TipoPagamentoEnum tpPagamento, float qtValorPago) : cdPagamento(cdPagamento), tpPagamento(tpPagamento), vlPagamento(qtValorPago) {}

int Pagamento::getCdPagamento() const { return cdPagamento; }
TipoPagamentoEnum Pagamento::getTpPagamento() const { return tpPagamento; }
float Pagamento::getVlPagamento() const {return vlPagamento;}

Pagamento::Pagamento() : cdPagamento(0), tpPagamento(), vlPagamento(0) {}
Pagamento::Pagamento(int cdPagamento, TipoPagamentoEnum tpPagamento): cdPagamento(cdPagamento), tpPagamento(tpPagamento) {}

Pagamento::Pagamento(int cdPagamento) : cdPagamento(cdPagamento), tpPagamento(), vlPagamento(0) {}

void Pagamento::setCdPagamento(int cdPagamento) {
    this->cdPagamento = cdPagamento;
}

void Pagamento::setTpPagamento(TipoPagamentoEnum tpPagamento) {
    this->tpPagamento = tpPagamento;
}

void Pagamento::setVlPagamento(float vlPagamento) {
    this->vlPagamento = vlPagamento;
}
