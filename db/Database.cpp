#include "Database.hpp"
#include "../resources/EnvLoader.hpp"
#include <iostream>
#include <filesystem>

Database::Database() {
    EnvLoader& env = EnvLoader::getInstance();
    std::string config_path = std::filesystem::path(std::filesystem::current_path()) / "resources" / "config.env";

    if (!env.isLoaded()) {
        if (!env.loadFromFile("../resources/config.env")) {
            std::cerr << "Erro: Falha ao carregar arquivo config.env" << std::endl;
            conn = nullptr;
            return;
        }
    }

    try {
        std::string host = env.get("DB_HOST");
        int port = env.getInt("DB_PORT", 5432);
        std::string dbname = env.get("DB_NAME");
        std::string user = env.get("DB_USER");
        std::string password = env.get("DB_PASSWORD");

        if (host.empty() || dbname.empty() || user.empty() || password.empty()) {
            std::cerr << "Erro: Variáveis de ambiente obrigatórias não encontradas!" << std::endl;
            conn = nullptr;
            return;
        }

        const std::string connStr =
            "host=" + host +
            " port=" + std::to_string(port) +
            " dbname=" + dbname +
            " user=" + user +
            " password=" + password;

        conn = new pqxx::connection(connStr);

        if (conn->is_open()) {
            std::cout << "Conexão com banco de dados realizada com sucesso!" << std::endl;
            std::cout << "Conectado em: " << host << ":" << port << "/" << dbname << std::endl;
        } else {
            std::cerr << "Erro ao conectar com banco de dados" << std::endl;
        }

    } catch (const std::exception &e) {
        std::cerr << "Erro ao conectar no banco de dados: " << e.what() << std::endl;
        conn = nullptr;
    }
}

Database::~Database() {
    if (conn) {
        conn->disconnect();
        delete conn;
    }
}

pqxx::result Database::executarQuery(const std::string& sql) const {
    if (!conn) {
        throw std::runtime_error("Conexão com banco de dados não estabelecida");
    }

    pqxx::work txn(*conn);
    pqxx::result r = txn.exec(sql);
    txn.commit();
    return r;
}