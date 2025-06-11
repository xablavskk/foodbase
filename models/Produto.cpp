//
// Created by vmep on 6/6/25.
//

#include "Produto.hpp"
#include  <utility>
#include <string>

using namespace std;

Produto::Produto(const int id, std::string name, std::string description, double value, std::string status)
    : id(id),
      name(std::move(name)),
      description(std::move(description)),
      value(value),
      status(std::move(status)) {
}

int Produto::getId() const { return id; }

std::string Produto::getName() const { return name; }

std::string Produto::getDescription() const { return description; }

double Produto::getValue() const { return value; }

std::string Produto::getStatus() const { return status; }

Produto::Produto() : id(0), name(""), description(""), value(0), status("") {}

void Produto::setId(const int id) {
    this->id = id;
}

void Produto::setName(const std::string& name) {
    this->name = name;
}

void Produto::setDescription(const std::string& description) {
    this->description = description;
}

void Produto::setValue(const double value) {
    this->value = value;
}

void Produto::setStatus(const std::string& status) {
    this->status = status;
}



