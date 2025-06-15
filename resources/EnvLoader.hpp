#pragma once

#include <string>
#include <unordered_map>

class EnvLoader {
private:
    std::unordered_map<std::string, std::string> envVars;
    bool loaded = false;

    std::string trim(const std::string& str);

public:
    static EnvLoader& getInstance();

    bool loadFromFile(const std::string& filename);
    std::string get(const std::string& key, const std::string& defaultValue = "");
    int getInt(const std::string& key, int defaultValue = 0);
    bool isLoaded() const { return loaded; }
};