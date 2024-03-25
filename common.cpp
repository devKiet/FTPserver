#include <fstream>
#include <string>
#include <map>
#include <iostream>

struct Config {
    std::string server;
    std::string username;
    std::string password;
};

/// @brief trim
/// @param str
/// @return str
static std::string trim(const std::string& str) {
    size_t start = 0;
    size_t end = str.length();

    // Find the first non-whitespace character from the beginning
    while (start < end && std::isspace(str[start])) {
        ++start;
    }

    // Find the first non-whitespace character from the end
    while (end > start && std::isspace(str[end - 1])) {
        --end;
    }

    // Return the substring containing non-whitespace characters
    return str.substr(start, end - start);
}

/// @brief parseINIFile
/// @param filename
/// @return config
static Config readConfigFile(const std::string& filename) {
    Config config;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#' || line[0] == ';')
                continue;
            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos) {
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);
 
                value.erase(0, value.find_first_not_of(" \t\n\r\f\v"));
                value.erase(value.find_last_not_of(" \t\n\r\f\v") + 1);
                key = trim(key);
                value = trim(value);
                if (key == "server")
                    config.server = value;
                else if (key == "username")
                    config.username = value;
                else if (key == "password")
                    config.password = value;
            }
        }
        file.close();
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
    
    return config;
}