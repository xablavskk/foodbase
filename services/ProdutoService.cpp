#include "ProdutoService.hpp"
#include <iostream>
#pragma once

ProdutoService::ProdutoService(Database& dbRef) : db(dbRef) {}

Produto ProdutoService::salvarProduto(const Produto& produto) const {
    if (produto.getNmProduto().empty()) {
        throw std::invalid_argument("Nome do produto não pode ser vazio.");
    }

    std::stringstream ss;
    ss << "INSERT INTO produto (nm_produto, ds_produto, vl_produto, st_produto) VALUES ('"
       << produto.getNmProduto() << "', '"
       << produto.getDsProduto() << "', "
       << produto.getVlProduto() << ", '"
       << produto.getStProduto() << "') RETURNING cd_produto, nm_produto, ds_produto, vl_produto, st_produto;";

    auto result = db.executarQuery(ss.str());

    if (result.empty()) {
        throw std::runtime_error("Erro ao salvar produto: resultado vazio.");
    }

    int produtoId = result[0]["cd_produto"].as<int>();
    std::string nome = result[0]["nm_produto"].as<std::string>();
    std::string descricao = result[0]["ds_produto"].as<std::string>();
    double valorProduto = result[0]["vl_produto"].as<double>();
    std::string status = result[0]["st_produto"].as<std::string>();

    Produto novoProduto(produtoId, nome, descricao, valorProduto, status);

    return novoProduto;
}

Produto ProdutoService::buscarProdutoPorId(int id) const {
    if (id == 0) {
        throw std::invalid_argument("Id inválido.");
    }

    std::stringstream ss;
    ss << "SELECT * FROM produto WHERE cd_produto = " << id << ";";

    auto result = db.executarQuery(ss.str());

    if (result.empty()) {
        throw std::runtime_error("Erro ao buscar produto: resultado vazio.");
    }

    int produtoId = result[0]["cd_produto"].as<int>();
    std::string nome = result[0]["nm_produto"].as<std::string>();
    std::string descricao = result[0]["ds_produto"].as<std::string>();
    double valorProduto = result[0]["vl_produto"].as<double>();
    std::string status = result[0]["st_produto"].as<std::string>();


    std::cout<<"cd_produto"<<produtoId;
    std::cout<<"nm_produto"<<nome;
    std::cout<<"ds_produto"<<descricao;
    std::cout<<"vl_produto"<<valorProduto;
    std::cout<<"st_produto"<<status;

    Produto produtoEncontrado(produtoId, nome, descricao, valorProduto, status);

    return produtoEncontrado;
}

Produto ProdutoService::atualizarProduto(const Produto& produto) const {
    if (produto.getCdProduto() == 0) {
        throw std::invalid_argument("ID inválido.");
    }

    std::stringstream ss;
    ss << "UPDATE produto SET "
       << "nm_produto = '" << produto.getNmProduto() << "', "
       << "ds_produto = '" << produto.getDsProduto() << "', "
       << "vl_produto = " << produto.getVlProduto() << ", "
       << "st_produto = '" << produto.getStProduto() << "' "
       << "WHERE cd_produto = " << produto.getCdProduto() << " RETURNING cd_produto, nm_produto, ds_produto, vl_produto, st_produto;";

    auto result = db.executarQuery(ss.str());

    int produtoId = result[0]["cd_produto"].as<int>();
    std::string nome = result[0]["nm_produto"].as<std::string>();
    std::string descricao = result[0]["ds_produto"].as<std::string>();
    double valorProduto = result[0]["vl_produto"].as<double>();
    std::string status = result[0]["st_produto"].as<std::string>();

    Produto produtoAtualizado(produtoId, nome, descricao, valorProduto, status);

    std::cout << "Produto atualizado com sucesso.\n";

    return produtoAtualizado;
}

void ProdutoService::deletarProduto(int id){
    if (id == 0) {
        throw std::invalid_argument("ID inválido.");
    }

    std::stringstream ss;
    ss << "DELETE FROM produto WHERE cd_produto = " << id << ";";

    auto result = db.executarQuery(ss.str());
}
