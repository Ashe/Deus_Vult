#include "LuaFunctions.h"

void lfs::loadFunctions(sol::state& lua) {
	// Load all of the entities & functions below into lua for use
	// VERY important function, scripting breaks if things aren't loaded

	// ~~~~~~~~~~~~~~~~
	// FUNCTIONS
	// ~~~~~~~~~~~~~~~~

	// Load entity
	lua.set_function("loadEntity", &EntityList::loadEntity);

	// Load map
	lua.set_function("loadMap", &MapManager::loadMap);
	lua.set_function("changeMap", &MapManager::changeMap);

	// Multi-purpose ping function on script component
	lua.set_function("ping", &lfs::ping);
	lua.set_function("pingTag", &lfs::pingTag);

	// NPC Component
	lua.set_function("printPhrase", &lfs::npcc_printPhrase);
	lua.set_function("npcc_setShowMessage", &lfs::npcc_setShowMessage);
	lua.set_function("npcc_setMessage", &lfs::npcc_setMessage);
	lua.set_function("npcc_sayMessage", &lfs::npcc_sayMessage);

	// Interaction Component
	lua.set_function("ic_interact", &EntityList::interactWithClosest);
	lua.set_function("ic_enableIntPrompt", &lfs::ic_enableIntPrompt);

	// Movement Component
	lua.set_function("mc_move", &lfs::mc_move);
	lua.set_function("mc_setSpeed", &lfs::mc_setSpeed);
	lua.set_function("mc_setLockMovement", &lfs::mc_setLockMovement);
	lua.set_function("mc_moveToMidpoint", &lfs::mc_moveToMidpoint);

	// Combat Component
	lua.set_function("cc_isInCombat", &lfs::cc_isInCombat);
	lua.set_function("cc_setInCombat", &lfs::cc_setInCombat);
}

bool lfs::ping(const sol::this_state& ts, const std::string& message, Entity* e) {
	auto sc = e->get<ScriptComponent>();
	if (sc) {
		sc->ping(message);
		return true;
	}

	return false;
}

bool lfs::pingTag(const sol::this_state& ts, const std::string& message, const std::string& tag) {

	auto entList = EntityList::getEntitiesFromTag(tag);
	bool success = false;

	for (auto &e : entList) {
		auto sc = e->get<ScriptComponent>();
		if (sc) {
			sc->ping(message);
			success = true;
		}
	}

	return success;
}

bool lfs::npcc_printPhrase(const sol::this_state& ts, Entity* e) {
	auto temp = e->get<NpcComponent>();
	temp->printText();

	return true;
}

bool lfs::npcc_setShowMessage(const sol::this_state& ts, Entity* e, bool show) {
	auto npc = e->get<NpcComponent>();
	if (npc) {
		npc->setShowText(show);
		return true;
	}
	return false;
}

bool lfs::npcc_setMessage(const sol::this_state& ts, Entity* e, const std::string& msg) {
	auto npc = e->get<NpcComponent>();
	if (npc) {
		npc->setTextString(msg);
		return true;
	}
	return false;
}

bool lfs::npcc_sayMessage(const sol::this_state& ts, Entity* e, const std::string& msg) {
	auto npc = e->get<NpcComponent>();
	if (npc) {
		npc->setTextString(msg);
		npc->setShowText(true);
		return true;
	}
	return false;
}

bool lfs::ic_enableIntPrompt(const sol::this_state& ts, Entity* e, bool show) {
	auto inter = e->get<InteractionComponent>();
	if (inter) {
		inter->setShowInteractPrompt(show);
		return true;
	}
	return false;
}

bool lfs::mc_move(const sol::this_state& ts, Entity* e, bool right) {
	auto mc = e->get<MovementComponent>();
	if (mc) {
		mc->addDirection(right * 2 - 1);
		return true;
	}

	return false;;
}

bool lfs::mc_setSpeed(const sol::this_state& ts, Entity* e, int speed) {
	auto mc = e->get<MovementComponent>();
	if (mc) {
		mc->setSprintSpeed(speed);
		return true;
	}

	return false;;
}

bool lfs::mc_setLockMovement(const sol::this_state& ts, Entity* e, bool lock) {
	auto mc = e->get<MovementComponent>();
	if (mc) {
		mc->setLockMovement(lock);
		return true;
	}

	return false;
}

bool lfs::mc_moveToMidpoint(const sol::this_state& ts, Entity* e) {
	auto mc = e->get<MovementComponent>();
	if (mc) {
		mc->moveToMidpoint();
		return true;
	}

	return false;
}

bool lfs::cc_isInCombat(const sol::this_state & ts, Entity * e)
{
	auto cc = e->get<CombatComponent>();
	if (cc) {
		return cc->isInCombat();
	}

	return false;
}

bool lfs::cc_setInCombat(const sol::this_state& ts, Entity* e, bool inCombat) {
	auto cc = e->get<CombatComponent>();
	if (cc) {
		cc->setInCombat(inCombat);
		return true;
	}

	return false;
}
