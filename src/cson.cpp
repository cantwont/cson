#include <iostream>
#include <fstream>
#include <windows.h>
#include "../include/json.hpp"

class JSONDatabase {
private:
    std::string filePath;
    std::string dbName;

public:
    JSONDatabase(const std::string& path, const std::string& name) : filePath(path), dbName(name) {}

    void createDatabase() {
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

    void setJsonVal(const std::string& key, const nlohmann::json& value) {
        std::string databasePath = filePath + "/" + dbName + ".json"; // Construct the full file path including the file name

        // Read existing database file
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

        // Update the JSON object with the new value
        database[key] = value;

        // Write the updated JSON object back to the file
        std::ofstream outFile(databasePath, std::ofstream::out | std::ofstream::trunc); // Open file in write mode and truncate it
        if (outFile.is_open()) {
            outFile << std::setw(4) << database;
            outFile.close();
            std::cout << "Value set successfully for key '" << key << "'" << std::endl;
        }
        else {
            std::cerr << "Error: Unable to open database file for writing" << std::endl;
        }
    }

private:
    std::wstring stringToWideString(const std::string& str) {
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
        std::wstring wide_str(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wide_str[0], size_needed);
        return wide_str;
    }
};

int main() {
    JSONDatabase database("database", "hi");
    database.createDatabase();
    database.setJsonVal("userInfo", { { "id", 123456789 } , { "username", "xiangs a bitch" }});
    database.setJsonVal("debug", TRUE);
    return 0;
}
