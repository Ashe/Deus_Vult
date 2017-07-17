#include "../Core/ResourceManagers/EntityList.h"

#include "../Core/Common/Scripts.h"

// Entity Interaction Functions
namespace lfs {

	// Load all the functions in the lfs namespace into lua
	void loadFunctions(sol::state& lua);

	// ~~~~~~~~~~~~~~~~
	// Script Component
	// ~~~~~~~~~~~~~~~~

	// Send the entity (or tag) a message
	bool ping(const sol::this_state&, const std::string& message, Entity* e);
	bool pingTag(const sol::this_state&, const std::string& message, const std::string& tag);

	// ~~~~~~~~~~~~~~~~
	// NPC Component
	// ~~~~~~~~~~~~~~~~

	// Print the message of an NPC to console
	bool npcc_printPhrase(const sol::this_state& ts, Entity* e);

	// Show or hide messages on an NPC
	bool npcc_setShowMessage(const sol::this_state& ts, Entity* e, bool show);

	// Set the message for an NPC to say
	bool npcc_setMessage(const sol::this_state& ts, Entity* e, const std::string& msg);

	// Makes an NPC say the phrase (combination of setMessage and showMessage)
	bool npcc_sayMessage(const sol::this_state& ts, Entity* e, const std::string& msg);

	// ~~~~~~~~~~~~~~~~
	// Interaction Component
	// ~~~~~~~~~~~~~~~~

	// Enable or disable the interact prompt on an NPC
	bool ic_enableIntPrompt(const sol::this_state& ts, Entity* e, bool show);

	// ~~~~~~~~~~~~~~~~
	// Movement Component
	// ~~~~~~~~~~~~~~~~

	// Adds direction right (or left if false) of the entity
	bool mc_move(const sol::this_state& ts, Entity* e, bool right);
	
	// Sets the speed of the entity. If coded properly, running animations are automatic
	bool mc_setSpeed(const sol::this_state& ts, Entity* e, int speed);

	// Enable or disable player-controlled movement
	bool mc_setLockMovement(const sol::this_state& ts, Entity* e, bool lock);

	// Command the entity to move to the nearest midpoint
	bool mc_moveToMidpoint(const sol::this_state& ts, Entity* e);

	// ~~~~~~~~~~~~~~~~
	// Combat Component
	// ~~~~~~~~~~~~~~~~

	// Get whether entity is in combat
	bool cc_isInCombat(const sol::this_state& ts, Entity* e);

	// Enable or Disable combat mode on an entity
	bool cc_setInCombat(const sol::this_state& ts, Entity* e, bool inCombat);

}