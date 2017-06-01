#include "Scripts.h"


void luah::printError(const std::string & variableName, const std::string & reason){
	printf("Error: can't get [%s] %s\n)", variableName.c_str(), reason.c_str());
}

bool luah::loadScript(sol::state& lua, const std::string& filename){
	sol::protected_function_result result = lua.script_file("Data/" + filename, sol::simple_on_error);
	if (!result.valid()) {
		sol::error err = result;
		sol::call_status status = result.status();
		printf("Something went horribly wrong: %s error \n\t %s\n", sol::to_string(status), err.what());
		return false;
	}
	return true;
}

bool luah::loadScript(sol::state_view& lua, const std::string & filename) {
	sol::protected_function_result result = lua.script_file("Data/" + filename, sol::simple_on_error);
	if (!result.valid()) {
		sol::error err = result;
		sol::call_status status = result.status();
		printf("Something went horribly wrong: %s error \n\t %s\n", sol::to_string(status), err.what());
		return false;
	}
	return true;
}