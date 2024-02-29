#include "cson.hpp"

int main() {
	JSONDatabase database("database", "hello");
	database.createDatabase();
	database.setJsonVal("userInfo", { {"id", 350858391519756298}, {"username", "cantwont"} });
	database.setJsonVal("userSettings", { {"language", "english"}, {"notifications", true} });

	nlohmann::json userInfo = database.getJsonVal("userInfo");
	nlohmann::json userSettings = database.getJsonVal("userSettings");

	std::cout << "User Info: " << userInfo << std::endl;
	std::cout << "Settings: " << userSettings << std::endl;

	return 0;
}