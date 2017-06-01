#ifndef SCRIPTS_H
#define SCRIPTS_H

#include <sol.hpp>

struct lua_State;

namespace luah {
	void printError(const std::string& variableName, const std::string& reason);
	bool loadScript(sol::state& lua, const std::string& filename);
	bool loadScript(sol::state_view& lua, const std::string& filename);
}

#endif