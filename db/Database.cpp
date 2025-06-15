#include "Database.hpp"
#include "../resources/EnvLoader.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <pqxx/pqxx>

bool executarScriptSQL(pqxx::connection* conn, const std::string& caminhoArquivo) {
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "[ERRO] Não foi possível abrir o arquivo: " << caminhoArquivo << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << arquivo.rdbuf();
    std::string sql = buffer.str();

    try {
        pqxx::work txn(*conn);
        txn.exec(sql);
        txn.commit();
        std::cout << "[INFO] Script SQL executado com sucesso!" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[ERRO] Falha ao executar SQL: " << e.what() << std::endl;
        return false;
    }
}

Database::Database() {
    EnvLoader& env = EnvLoader::getInstance();

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

            if (!executarScriptSQL(conn, "../db/schema.sql")) {
                std::cerr << "[ERRO] Erro ao executar schema.sql" << std::endl;
                return;
            }
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
        conn->close();
        delete conn;
    }
}

pqxx::connection* Database::getConnection() const {
    return conn;
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