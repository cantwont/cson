#ifndef CSON_HPP
#define CSON_HPP

#include <iostream>
#include <fstream>
#include <windows.h>
#include "include/json.hpp"

class JSONDatabase {
private:
	std::string filePath;
	std::string dbName;

public:
	JSONDatabase(const std::string& path, const std::string& name);

	void createDatabase();

	void setJsonVal(const std::string& key, const nlohmann::json& value);

private:
	std::wstring stringToWideString(const std::string& str);
};


#endif /* CSON_HPP */