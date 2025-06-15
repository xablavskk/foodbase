//
// Created by vmep on 6/6/25.
//
#pragma once

#include <string>

#include "Produto.hpp"
#include "../db/Database.hpp"



class ProdutoService {

    private:
        Database& db;

    public:
        ProdutoService(Database& dbRef);
        Produto salvarProduto(const Produto& produto) const;
        Produto buscarProdutoPorId(int id) const;
        Produto atualizarProduto(const Produto& produto) const;
        void deletarProduto(int id);
};





