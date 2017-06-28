#include "LuaFunctions.h"

void lfs::loadFunctions(sol::state & lua) {
	// Load all of the entities & functions below into lua for use
	// VERY important function, scripting breaks if things aren't loaded

	// ~~~~~~~~~~~~~~~~
	// FUNCTIONS
	// ~~~~~~~~~~~~~~~~

	// NPC Component
	lua.set_function("printPhrase", &lfs::printPhrase);
	lua.set_function("setShowMessage", &lfs::setShowMessage);
	lua.set_function("setMessage", &lfs::setMessage);
	lua.set_function("sayMessage", &lfs::sayMessage);

	// Interaction Component
	lua.set_function("enableIntPrompt", &lfs::enableIntPrompt);

	// ~~~~~~~~~~~~~~~~
	// ENTITIES
	// ~~~~~~~~~~~~~~~~

	lua.set_function("loadEntity", &EntityList::loadEntity);
	luah::loadScript(lua, "player/player.lua");
	luah::loadScript(lua, "npcs/bruh/bruh.lua");

	// ~~~~~~~~~~~~~~~~
	// EXECUTE NOW
	// ~~~~~~~~~~~~~~~~

	luah::loadScript(lua, "common/scripts/makePlayer.lua");

}

bool lfs::printPhrase(const sol::this_state& ts, Entity* e) {
	auto temp = e->get<NpcComponent>();
	temp->printText();

	return true;
}

bool lfs::setShowMessage(const sol::this_state& ts, Entity* e, bool show) {
	auto npc = e->get<NpcComponent>();
	if (npc) {
		npc->setShowText(show);
		return true;
	}
	return false;
}

bool lfs::setMessage(const sol::this_state& ts, Entity* e, const std::string& msg) {
	auto npc = e->get<NpcComponent>();
	if (npc) {
		npc->setTextString(msg);
		return true;
	}
	return false;
}

bool lfs::sayMessage(const sol::this_state& ts, Entity* e, const std::string& msg) {
	auto npc = e->get<NpcComponent>();
	if (npc) {
		npc->setTextString(msg);
		npc->setShowText(true);
		return true;
	}
	return false;
}

bool lfs::enableIntPrompt(const sol::this_state& ts, Entity* e, bool show) {
	auto inter = e->get<InteractionComponent>();
	if (inter) {
		inter->setShowInteractPrompt(show);
		return true;
	}
	return false;
}
