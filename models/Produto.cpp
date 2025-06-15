//
// Created by vmep on 6/6/25.
//

#include "Produto.hpp"
#include  <utility>
#include <string>

using namespace std;

Produto::Produto(const int cdProduto, std::string nmProduto, std::string dsProduto, double vlProduto, std::string stProduto)
    : cdProduto(cdProduto),
      nmProduto(std::move(nmProduto)),
      dsProduto(std::move(dsProduto)),
      vlProduto(vlProduto),
      stProduto(std::move(stProduto)) {
}

Produto::Produto() : cdProduto(0), nmProduto(""), dsProduto(""), vlProduto(0), stProduto("") {}

Produto::Produto(string nmProduto, string dsProduto, double vlProduto, string stProduto) : nmProduto(nmProduto), dsProduto(dsProduto), vlProduto(vlProduto), stProduto(stProduto) {};

int Produto::getCdProduto() const { return cdProduto; }

std::string Produto::getNmProduto() const { return nmProduto; }

std::string Produto::getDsProduto() const { return dsProduto; }

double Produto::getVlProduto() const { return vlProduto; }

std::string Produto::getStProduto() const { return stProduto; }

void Produto::setCdProduto(const int cdProduto) {
    this->cdProduto = cdProduto;
}

void Produto::setNmProduto(const std::string& nmProduto) {
    this->nmProduto = nmProduto;
}

void Produto::setDsProduto(const std::string& dsProduto) {
    this->dsProduto = dsProduto;
}

void Produto::setVlProduto(const double vlProduto) {
    this->vlProduto = vlProduto;
}

void Produto::setStProduto(const std::string& stProduto) {
    this->stProduto = stProduto;
}



