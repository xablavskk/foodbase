#pragma once
#include <string>

class Pedido {
private:
    int id;
    std::string name;


    // [[nodiscard]] em C++ serve para indicar
    // ao compilador que o valor de retorno de uma função
    // não deve ser ignorado. Se for ignorado, o compilador gera um warning (aviso)
public:
    Pedido(int id, std::string nome);

    Pedido();

    [[nodiscard]] int getId() const;
    [[nodiscard]] std::string getName() const;

    void setName(const std::string& name);
    void setId(int id);
};
