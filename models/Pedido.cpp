#include "Pedido.hpp"

#include <utility>

#include "../db/Database.hpp"

//Construtor
Pedido::Pedido(int cd_pedido, int pagamento_cd_pagamento, int produto_cd_produto, std::string st_pedido)
    : cd_pedido(cd_pedido),
      pagamento_cd_pagamento(pagamento_cd_pagamento),
      produto_cd_produto(produto_cd_produto),
      st_pedido(std::move(st_pedido)) {}

// Construtor vazio
Pedido::Pedido() : cd_pedido(0), pagamento_cd_pagamento(0), produto_cd_produto(0), st_pedido("") {}


//Gets e sets
int Pedido::getCdPedido() const {
    return cd_pedido;
}

int Pedido::getPagamento_cd_pagamento() const {
    return pagamento_cd_pagamento;
}

int Pedido::getProduto_cd_produto() const {
    return produto_cd_produto;
}

std::string Pedido::getStPedido() const {
    return st_pedido;
}

void Pedido::setCdPedido(int cd_pedido) {
    this-> cd_pedido;
}

void Pedido::setPagamento_cd_pagamento(int pagamento_cd_pagamento) {
    this-> pagamento_cd_pagamento;
}

void Pedido::setProduto_cd_produto(int produto_cd_produto) {
    this-> produto_cd_produto;
}

void Pedido::setStPedido(std::string& st_pedido) {
    this-> st_pedido;
}