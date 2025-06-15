#include "Pedido.hpp"
#include "Pagamento.hpp"
#include "Produto.hpp"
#include <utility>

#include "../db/Database.hpp"

//Construtor
Pedido::Pedido(int cdPedido, Pagamento* pagamento, Produto* produto, std::string stPedido)
    : cdPedido(cdPedido),
      pagamento(pagamento),
      produto(produto),
      stPedido(std::move(stPedido)) {}

// Construtor vazio
Pedido::Pedido() : cdPedido(0), pagamento(nullptr), produto(nullptr), stPedido("") {}

Pedido::Pedido(Pagamento *pagamento, Produto* produto, std::string stPedido) : cdPedido(0), pagamento(pagamento),
    produto(produto), stPedido(std::move(stPedido)) {
}

Pedido::Pedido(Pagamento *pagamento, std::string stPedido) : cdPedido(0), pagamento(pagamento), produto(nullptr),
                                                             stPedido(std::move(stPedido)) {
}

Pedido::Pedido(int cdPedido, Pagamento *pagamento, std::string stPedido) : cdPedido(cdPedido), pagamento(pagamento), produto(nullptr),
                                                             stPedido(std::move(stPedido)) {
}


//Gets e sets
int Pedido::getCdPedido() const {
    return cdPedido;
}

Pagamento* Pedido::getPagamento() const {
    return pagamento;
}

Produto* Pedido::getProduto() const {
    return produto;
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

void Pedido::setProduto(Produto* produto) {
    this-> produto = produto;
}

void Pedido::setStPedido(std::string& stPedido) {
    this-> stPedido = stPedido;
}