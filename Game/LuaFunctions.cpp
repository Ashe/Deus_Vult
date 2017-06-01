#include "LuaFunctions.h"

void lfs::loadFunctions(sol::state & lua) {
	lua.set_function("loadEntity", &EntityList::loadEntity);
	luah::loadScript(lua, "player/player.lua");
	luah::loadScript(lua, "bruh/bruh.lua");
	lua.set_function("printPhrase", &lfs::printPhrase);

	luah::loadScript(lua, "common/scripts/makePlayer.lua");

}

void lfs::printPhrase(const sol::this_state& ts, Entity* e) {
	auto temp = e->get<NpcComponent>();
	temp->printPhrase();
}