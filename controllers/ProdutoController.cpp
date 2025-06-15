//
// Created by vmep on 6/6/25.
//

#include "ProdutoController.hpp"


ProdutoController::ProdutoController() : service(db) {}

Produto ProdutoController::salvarProduto(const Produto& produto) const {
    return service.salvarProduto(produto);
}

Produto ProdutoController::buscarProdutoPorId(int id) const {
    return service.buscarProdutoPorId(id);
}

Produto ProdutoController::atualizarProduto(const Produto &produto) const {
    return service.atualizarProduto(produto);
}

void ProdutoController::deletarProduto(int id) {
    service.deletarProduto(id);
}


