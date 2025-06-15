#pragma once
#include <pqxx/pqxx>
#include <string>

class Database {
private:
    pqxx::connection* conn;

public:
    Database();
    ~Database();
    pqxx::result executarQuery(const std::string& sql) const;
    pqxx::connection* getConnection() const;
};