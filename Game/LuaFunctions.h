#include "../Core/ResourceManagers/EntityList.h"

#include "../Core/Common/Scripts.h"

// Entity Interaction Functions
namespace lfs {
	// Load all the functions in the lfs namespace into lua
	void loadFunctions(sol::state& lua);

	// Print NPC phrase
	void printPhrase(const sol::this_state& ts, Entity* e);
}