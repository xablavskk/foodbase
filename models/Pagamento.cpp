#include "Pagamento.hpp" // inclui o header da classe pagamento

// construtor que inicializa todos os atributos com os valores recebidos
Pagamento::Pagamento(const int cdPagamento, TipoPagamentoEnum tpPagamento, double qtValorPago) : cdPagamento(cdPagamento), tpPagamento(tpPagamento), vlPagamento(qtValorPago) {}

// retorna o codigo do pagamento
int Pagamento::getCdPagamento() const { return cdPagamento; }

// retorna o tipo de pagamento
TipoPagamentoEnum Pagamento::getTpPagamento() const { return tpPagamento; }

// retorna o valor do pagamento
double Pagamento::getVlPagamento() const { return vlPagamento; }

// construtor padrao que inicializa os atributos com valores default
Pagamento::Pagamento() : cdPagamento(0), tpPagamento(), vlPagamento(0) {}

// construtor que recebe codigo e tipo de pagamento
Pagamento::Pagamento(int cdPagamento, TipoPagamentoEnum tpPagamento)
    : cdPagamento(cdPagamento), tpPagamento(tpPagamento) {}

// construtor que recebe tipo de pagamento e valor do pagamento
Pagamento::Pagamento(TipoPagamentoEnum tpPagamento, double vlPagamento) : cdPagamento(0), tpPagamento(tpPagamento),
                                                                         vlPagamento(vlPagamento) {}


// construtor que recebe apenas o codigo do pagamento
Pagamento::Pagamento(int cdPagamento)
    : cdPagamento(cdPagamento), tpPagamento(), vlPagamento(0) {}

// define o codigo do pagamento
void Pagamento::setCdPagamento(int cdPagamento) {
    this->cdPagamento = cdPagamento;
}

// define o tipo do pagamento
void Pagamento::setTpPagamento(TipoPagamentoEnum tpPagamento) {
    this->tpPagamento = tpPagamento;
}

// define o valor do pagamento
void Pagamento::setVlPagamento(double vlPagamento) {
    this->vlPagamento = vlPagamento;
}
