//
// Created by vmep on 6/6/25.
//
#pragma once

#include "../models/Produto.hpp"
#include "../services/ProdutoService.hpp"
#include "../db/Database.hpp"




class ProdutoController {

private:
    Database db;
    ProdutoService service;

public:
    ProdutoController();
    Produto salvarProduto(const Produto& produto) const;
    Produto buscarProdutoPorId(int id) const;
    Produto atualizarProduto(const Produto& produto) const;
    void deletarProduto(int id);
};




