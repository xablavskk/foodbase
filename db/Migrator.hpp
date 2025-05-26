#pragma once
#include "Database.hpp"
#include &lt;vector&gt;
#include &lt;functional&gt;

class DatabaseMigrator {
    inline static std::vector&lt;std::function&lt;void(soci::session&amp;)&gt;&gt; migrations = {
        [](soci::session&amp; sql) {
            sql &lt;&lt; "CREATE TABLE IF NOT EXISTS schema_version ("
                "version INTEGER PRIMARY KEY"
                ")";
            sql &lt;&lt; "INSERT INTO schema_version (version) VALUES (0)";
        },
        [](soci::session&amp; sql) {
            sql &lt;&lt; "CREATE TABLE IF NOT EXISTS pedidos ("
                "id INTEGER PRIMARY KEY, "
                "nome TEXT NOT NULL DEFAULT '', "
                "data_criacao TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP"
                ")";
        },
        [](soci::session&amp; sql) {
            sql &lt;&lt; "ALTER TABLE pedidos ADD COLUMN status TEXT NOT NULL DEFAULT 'PENDENTE'";
        }
    };

public:
    static void runMigrations() {
        auto&amp; db = Database::getInstance();
        soci::transaction tr(db.getSession());
        
        try {
            int currentVersion = 0;
            
            // Verifica se a tabela de versão já existe
            if(db.getSession().table_exists("schema_version")) {
                db.getSession() &lt;&lt; "SELECT version FROM schema_version", 
                    soci::into(currentVersion);
            }

            // Executa migrações pendentes
            for (size_t i = currentVersion; i &lt; migrations.size(); ++i) {
                migrations[i](db.getSession());
                db.getSession() &lt;&lt; "UPDATE schema_version SET version = :versao",
                    soci::use(static_cast&lt;int&gt;(i+1));
            }
            
            tr.commit();
        } catch (const std::exception&amp; e) {
            tr.rollback();
            throw std::runtime_error("Falha na migração: " + std::string(e.what()));
        }
    }
};

