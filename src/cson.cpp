#include "../cson.hpp"

JSONDatabase::JSONDatabase(const std::string& path, const std::string& name) : filePath(path), dbName(name) {}

void JSONDatabase::createDatabase() {
    nlohmann::json database = nlohmann::json::object();

    if (!CreateDirectoryW(stringToWideString(filePath).c_str(), NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
        std::cerr << "Error: Unable to create directory at " << filePath << std::endl;
        return;
    }

    std::ofstream file(filePath + "/" + dbName + ".json");

    if (file.is_open()) {
        file << database.dump(4);
        std::cout << "Database '" << dbName << "' created successfully at " << filePath << std::endl;
    }
    else {
        std::cerr << "Error: Unable to create database file at " << filePath << "/" << dbName << ".json" << std::endl;
    }
}

void JSONDatabase::setJsonVal(const std::string& key, const nlohmann::json& value) {
    std::string databasePath = filePath + "/" + dbName + ".json";

    std::ifstream file(databasePath);
    nlohmann::json database;
    if (file.is_open()) {
        file >> database;
        file.close();
    }
    else {
        std::cerr << "Error: Unable to open database file for reading" << std::endl;
        return;
    }

    database[key] = value;

    std::ofstream outFile(databasePath, std::ofstream::out | std::ofstream::trunc);
    if (outFile.is_open()) {
        outFile << std::setw(4) << database;
        outFile.close();
        std::cout << "Value set successfully for key '" << key << "'" << std::endl;
    }
    else {
        std::cerr << "Error: Unable to open database file for writing" << std::endl;
    }
}

nlohmann::json JSONDatabase::getJsonVal(const std::string& key) {
    std::string databasePath = filePath + "/" + dbName + ".json";

    std::ifstream file(databasePath);
    nlohmann::json database;
    if (file.is_open()) {
        file >> database;
        file.close();
    }
    else {
        std::cerr << "Error: Unable to open database file for reading" << std::endl;
        return nlohmann::json();
    }

    if (database.find(key) != database.end()) {
        return database[key];
    }
    else {
        std::cerr << "Error: Key '" << key << "' not found in the database" << std::endl;
        return nlohmann::json();
    }
}

std::wstring JSONDatabase::stringToWideString(const std::string& str) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wide_str(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wide_str[0], size_needed);
    return wide_str;
}
