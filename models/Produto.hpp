//
// Created by vmep on 6/6/25.
//
#pragma once
#include <string>
using namespace std;



class Produto {

private:
    int id;
    string name;
    string description;
    double value;
    string status;

public:
    Produto(int id, string name, string description, double value, string status);

    Produto();


    // [[nodiscard]] em C++ serve para indicar
    // ao compilador que o valor de retorno de uma função
    // não deve ser ignorado. Se for ignorado, o compilador gera um warning (aviso)

    [[nodiscard]] int getId() const;
    [[nodiscard]] string getName() const;
    [[nodiscard]] string getDescription() const;
    [[nodiscard]] double getValue() const;
    [[nodiscard]] string getStatus() const;

    void setId(int id);
    void setName(const std::string& name);
    void setDescription(const std::string& description);
    void setValue(double value);
    void setStatus(const std::string& status);

};
