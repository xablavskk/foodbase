#include "Database.hpp"
#include "db_config.h"
#include <iostream>


Database::Database() {
    try {
        const std::string connStr =
            "host=" + std::string(DB_HOST) +
            " port=" + std::to_string(DB_PORT) +
            " dbname=" + DB_NAME +
            " user=" + DB_USER +
            " password=" + DB_PASSWORD;

        conn = new pqxx::connection(connStr);

        if (conn->is_open()) {
            std::cout << "a conexao foi feita com sucesso." << std::endl;
        } else {
            std::cerr << "erro ao conectar com banco de dados" << std::endl;
        }

    } catch (const std::exception &e) {
        std::cerr << "Erro ao conectar no banco de dados: " << e.what() << std::endl;
        conn = nullptr; // importante para evitar acesso posterior invalido
    }
}

Database::~Database() {
    if (conn) {
        conn->disconnect();
        delete conn;
    }
}


pqxx::result Database::executarQuery(const std::string& sql) const {
    pqxx::work txn(*conn);
    pqxx::result r = txn.exec(sql);
    txn.commit();
    return r;
}
