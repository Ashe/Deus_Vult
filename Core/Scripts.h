#ifndef SCRIPTS_H
#define SCRIPTS_H

#include <sol.hpp>

struct lua_State;

namespace luah {
	void printError(const std::string& variableName, const std::string& reason);
	bool loadScript(lua_State* L, const std::string& filename);

	void lua_gettostack(lua_State* L, const std::string& variableName);
	void loadGetKeysFunction(lua_State* L);
	std::vector<std::string> getTableKeys(lua_State* L, const std::string& name);
}

#endif