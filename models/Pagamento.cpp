
#include "Pagamento.hpp"

Pagamento::Pagamento(const int cdPagamento, TipoPagamentoEnum tpPagamento, float qtValorPago) : cdPagamento(cdPagamento), tpPagamento(tpPagamento), qtValorPago(qtValorPago) {}

int Pagamento::getCdPagamento() const { return cdPagamento; }
TipoPagamentoEnum Pagamento::getTpPagamento() const { return tpPagamento; }
float Pagamento::getQtValorPago() const {return qtValorPago;}

Pagamento::Pagamento() : cdPagamento(0), tpPagamento(), qtValorPago(0) {}
Pagamento::Pagamento(int cdPagamento) : cdPagamento(cdPagamento), tpPagamento(), qtValorPago(0) {}

void Pagamento::setCdPagamento(int cdPagamento) {
    this->cdPagamento = cdPagamento;
}

void Pagamento::setTpPagamento(TipoPagamentoEnum tpPagamento) {
    this->tpPagamento = tpPagamento;
}

void Pagamento::setQtValorPago(float qtValorPago) {
    this->qtValorPago = qtValorPago;
}
