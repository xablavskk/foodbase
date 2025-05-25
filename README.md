# 🚀 Projeto MVC em C++ com PostgreSQL (`libpqxx`)

Este projeto é uma aplicação exemplo no padrão MVC (Model-View-Controller) escrita em C++, utilizando a biblioteca `libpqxx` para comunicação com o banco de dados PostgreSQL.

---

## 📋 Requisitos

- C++17 ou superior
- CMake ≥ 3.10
- PostgreSQL instalado e rodando
- `libpqxx` (cliente C++ para PostgreSQL)
- Ambiente Linux ou WSL (Windows Subsystem for Linux)

---

## 🛠️ Instalação

### 🔹 Instale dependências no Ubuntu/WSL:

```bash
sudo apt update
sudo apt install libpqxx-dev libpq-dev cmake g++
```

### Clone este repositório:
- git clone https://github.com/seu-usuario/seu-repositorio.git
- cd seu-repositorio

### Estrutura do projeto:

project/
├── CMakeLists.txt
├── main.cpp
├── config/
│   └── db_config.h
├── db/
│   ├── Database.cpp
│   └── Database.hpp
├── models/
│   ├── Pedido.cpp
│   └── Pedido.hpp
├── controllers/
│   ├── PedidoController.cpp
│   └── PedidoController.hpp

### Config do banco de dados
- sudo -i -u postgres
- psql

### Editar o arquivo de config `config/db_config.h` com as variaveis de acordo com seu host/user do banco

### Processo de compilação:
-- mkdir build
-- cd build
-- cmake ..
-- make
