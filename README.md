# Projeto MVC em C++ com PostgreSQL (`libpqxx`)

Este projeto é uma aplicação exemplo no padrão MVC (Model-View-Controller) escrita em C++, utilizando a biblioteca `libpqxx` para comunicação com o banco de dados PostgreSQL e a biblioteca `crow.h` para chamadas http.

---

## Requisitos

- C++17 ou superior
- CMake ≥ 3.10
- PostgreSQL instalado e rodando
- `libpqxx` (cliente C++ para PostgreSQL)
- Ambiente Linux ou WSL (Windows Subsystem for Linux)
- `crow.h` para chamadas http

---

## Instalação

### Instale dependências no Ubuntu/WSL:

```bash
sudo apt-get update

sudo apt-get install postgresql-16
sudo apt-get install postgresql-server-dev-16
sudo apt-get install postgresql-client-16
sudo apt-get install libpqxx-dev libpq-dev cmake g++
sudo apt install libasio-dev
```
- git clone https://github.com/CrowCpp/Crow.git (no sistema wsl/linux para download da biblioteca no sistema)
- cd Crow
- mkdir build
- cd build/
- cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF
- sudo make install

### Config do banco de dados
- sudo -i -u (seu usuario)
- psql

## AVISO

### é necessário na pasta resources/ adicionar o arquivo config.env com as variáveis de conexao do banco
### exemplo da estrutura do arquivo com os parametros para conexao:

#### DB_HOST=localhost
#### DB_PORT=5432
#### DB_NAME=foodbase
#### DB_USER=postgres
#### DB_PASSWORD=root

### Processo de compilação (acesse a raiz do projeto):
-- mkdir build
-- cd build
-- cmake ..
-- make
