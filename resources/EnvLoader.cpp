#include "EnvLoader.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

EnvLoader& EnvLoader::getInstance() {
    static EnvLoader instance;
    return instance;
}

std::string EnvLoader::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

bool EnvLoader::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Erro: Não foi possível abrir o arquivo " << filename << std::endl;
        return false;
    }

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;

        line = trim(line);

        if (line.empty() || line[0] == '#') {
            continue;
        }

        size_t pos = line.find('=');
        if (pos == std::string::npos) {
            std::cerr << "Aviso: Linha " << lineNumber << " inválida no arquivo " << filename << std::endl;
            continue;
        }

        std::string key = trim(line.substr(0, pos));
        std::string value = trim(line.substr(pos + 1));

        if ((value.front() == '"' && value.back() == '"') ||
            (value.front() == '\'' && value.back() == '\'')) {
            value = value.substr(1, value.length() - 2);
        }

        envVars[key] = value;
    }

    file.close();
    loaded = true;

    std::cout << "Arquivo " << filename << " carregado com sucesso. "
              << envVars.size() << " variáveis carregadas." << std::endl;

    return true;
}

std::string EnvLoader::get(const std::string& key, const std::string& defaultValue) {
    auto it = envVars.find(key);
    if (it != envVars.end()) {
        return it->second;
    }

    const char* sysEnv = std::getenv(key.c_str());
    if (sysEnv != nullptr) {
        return std::string(sysEnv);
    }

    if (defaultValue.empty()) {
        std::cerr << "Aviso: Variável '" << key << "' não encontrada!" << std::endl;
    }

    return defaultValue;
}

int EnvLoader::getInt(const std::string& key, int defaultValue) {
    std::string value = get(key);
    if (value.empty()) {
        return defaultValue;
    }

    try {
        return std::stoi(value);
    } catch (const std::exception& e) {
        std::cerr << "Erro ao converter '" << key << "' para inteiro: " << e.what() << std::endl;
        return defaultValue;
    }
}