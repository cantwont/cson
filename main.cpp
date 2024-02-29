#include "cson.hpp"

int main() {
	JSONDatabase database("database", "hello");
	database.createDatabase();
	database.setJsonVal("userInfo", { {"id", 350858391519756298}, {"username", "cantwont"} });
	database.setJsonVal("userSettings", { {"language", "english"}, {"notifications", true} });
	return 0;
}