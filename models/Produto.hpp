//
// Created by vmep on 6/6/25.
//
#pragma once
#include <string>
using namespace std;



class Produto {

private:
    int cdProduto;
    string nmProduto;
    string dsProduto;
    double vlProduto;
    string stProduto;

public:
    Produto(int cdProduto, string nmProduto, string dsProduto, double vlProduto, string stProduto);
    Produto(string nmProduto, string dsProduto, double vlProduto, string stProduto);
    Produto();


    // [[nodiscard]] em C++ serve para indicar
    // ao compilador que o valor de retorno de uma função
    // não deve ser ignorado. Se for ignorado, o compilador gera um warning (aviso)

    [[nodiscard]] int getCdProduto() const;
    [[nodiscard]] string getNmProduto() const;
    [[nodiscard]] string getDsProduto() const;
    [[nodiscard]] double getVlProduto() const;
    [[nodiscard]] string getStProduto() const;

    void setCdProduto(int cdProduto);
    void setNmProduto(const std::string& nmProduto);
    void setDsProduto(const std::string& dsProduto);
    void setVlProduto(double vlProduto);
    void setStProduto(const std::string& stProduto);

};
