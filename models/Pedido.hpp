#pragma once
#include <string>
#include "Pagamento.hpp"

class Pedido {
private:
    int cdPedido;
    Pagamento* pagamento;
    int produto_cd_produto;
    std::string stPedido;


    // [[nodiscard]] em C++ serve para indicar
    // ao compilador que o valor de retorno de uma função
    // não deve ser ignorado. Se for ignorado, o compilador gera um warning (aviso)

public:

    Pedido(int cdPedido, Pagamento* pagamento, int produto_cd_produto, std::string stPedido);
    Pedido(Pagamento* pagamento, int produto_cd_produto, std::string stPedido);
    Pedido(Pagamento* pagamento, std::string stPedido);
    Pedido();

    [[nodiscard]] int getCdPedido() const;
    [[nodiscard]] Pagamento* getPagamento() const;
    [[nodiscard]] int getProduto_cd_produto() const;
    [[nodiscard]] std::string getStPedido() const;


    void setCdPedido(int cdPedido);
    void setPagamento(Pagamento* pagamento);
    void setProduto_cd_produto(int produto);
    void setStPedido(std::string& status);
};
