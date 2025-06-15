#include "Pedido.hpp"
#include "Pagamento.hpp"
#include <utility>

#include "../db/Database.hpp"

//Construtor
Pedido::Pedido(int cdPedido, Pagamento* pagamento, int produto_cd_produto, std::string stPedido)
    : cdPedido(cdPedido),
      pagamento(pagamento),
      produto_cd_produto(produto_cd_produto),
      stPedido(std::move(stPedido)) {}

// Construtor vazio
Pedido::Pedido() : cdPedido(0), pagamento(nullptr), produto_cd_produto(0), stPedido("") {}

Pedido::Pedido(Pagamento *pagamento, int produto_cd_produto, std::string stPedido) : cdPedido(0), pagamento(pagamento),
    produto_cd_produto(produto_cd_produto), stPedido(std::move(stPedido)) {
}

Pedido::Pedido(Pagamento *pagamento, std::string stPedido) : cdPedido(0), pagamento(pagamento), produto_cd_produto(0),
                                                             stPedido(std::move(stPedido)) {
}


//Gets e sets
int Pedido::getCdPedido() const {
    return cdPedido;
}

Pagamento* Pedido::getPagamento() const {
    return pagamento;
}

int Pedido::getProduto_cd_produto() const {
    return produto_cd_produto;
}

std::string Pedido::getStPedido() const {
    return stPedido;
}

void Pedido::setCdPedido(int cdPedido) {
    this-> cdPedido = cdPedido;
}

void Pedido::setPagamento(Pagamento* pagamento) {
    this-> pagamento = pagamento;
}

void Pedido::setProduto_cd_produto(int produto_cd_produto) {
    this-> produto_cd_produto = produto_cd_produto;
}

void Pedido::setStPedido(std::string& stPedido) {
    this-> stPedido = stPedido;
}