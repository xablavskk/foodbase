#pragma once
#include <string>

class Pedido {
private:
    int cd_pedido;
    int pagamento_cd_pagamento;
    int produto_cd_produto;
    std::string st_pedido;


    // [[nodiscard]] em C++ serve para indicar
    // ao compilador que o valor de retorno de uma função
    // não deve ser ignorado. Se for ignorado, o compilador gera um warning (aviso)

public:

    Pedido(int cd_pedido, int pagamento_cd_pagamento, int produto_cd_produto, std::string st_pedido);

    Pedido();

    [[nodiscard]] int getCdPedido() const;
    [[nodiscard]] int getPagamento_cd_pagamento() const;
    [[nodiscard]] int getProduto_cd_produto() const;
    [[nodiscard]] std::string getStPedido() const;

    void setCdPedido(int id);   
    void setPagamento_cd_pagamento(int pagamento);  
    void setProduto_cd_produto(int produto);
    void setStPedido(std::string& status);
};
