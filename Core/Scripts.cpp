#include "Scripts.h"


void luah::printError(const std::string & variableName, const std::string & reason){
	printf("Error: can't get [%s] %s\n)", variableName.c_str(), reason.c_str());
}

bool luah::loadScript(lua_State * L, const std::string & filename){
	if (!(luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0))) {
		return true;
	}
	else {
		printf("Failed to load %s\n", filename.c_str());
		printf("%s\n", lua_tostring(L, -1));
		lua_pop(L, 1); // pop the error message from stack
		return false;
	}
}

void luah::loadGetKeysFunction(lua_State* L) {
	std::string code =
		R"(function getKeys(t)
        s = {}
        for k, v in pairs(t) do
            table.insert(s, k)
            end 
        return s 
        end)";
	luaL_dostring(L, code.c_str());
}

std::vector<std::string> luah::getTableKeys(lua_State* L, const std::string& name) {
	lua_getglobal(L, "getKeys"); // get function
	if (lua_isnil(L, -1)) {
		printf("\nGet keys function is not loaded. Loading...\n");
		loadGetKeysFunction(L);
		lua_getglobal(L, "getKeys");
	}

	lua_gettostack(L, name.c_str());

	lua_pcall(L, 1, 1, 0); // execute getKeys function.

	lua_pushnil(L);

	std::vector<std::string> keys;
	while (lua_next(L, -2)) { // get values one by one
		if (lua_type(L, -1) == LUA_TSTRING) { // check if key is a string
			keys.push_back(lua_tostring(L, -1));
		}
		lua_pop(L, 1);
	}

	lua_settop(L, 0); // remove s table from stack 
	return keys;
}

void luah::lua_gettostack(lua_State* L, const std::string& variableName) {
	int level = 0;
	std::string var = "";
	for (unsigned int i = 0; i < variableName.size(); i++) {
		if (variableName.at(i) == '.') {
			if (level == 0) {
				lua_getglobal(L, var.c_str());
			}
			else {
				lua_getfield(L, -1, var.c_str());
			}

			if (lua_isnil(L, -1)) {
				printf("Error, can't get %s.\n", variableName.c_str());
				return;
			}
			else {
				var = "";
				level++;
			}
		}
		else {
			var += variableName.at(i);
		}
	}
	if (level == 0) {
		lua_getglobal(L, var.c_str());
	}
	else {
		lua_getfield(L, -1, var.c_str());
	}

	if (level == 0) { return; } // no need to remove anything

	int tableIndex = lua_gettop(L) - level;
	lua_replace(L, tableIndex);
	lua_settop(L, tableIndex);
}
