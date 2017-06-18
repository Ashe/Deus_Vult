#include "../Core/ResourceManagers/EntityList.h"

#include "../Core/Common/Scripts.h"

// Entity Interaction Functions
namespace lfs {
	// Load all the functions in the lfs namespace into lua
	void loadFunctions(sol::state& lua);

	// Print the message of an NPC to console
	bool printPhrase(const sol::this_state& ts, Entity* e);

	// Show or hide messages on an NPC
	bool setShowMessage(const sol::this_state& ts, Entity* e, bool show);

	// Set the message for an NPC to say
	bool setMessage(const sol::this_state& ts, Entity* e, const std::string& msg);

	// Makes an NPC say the phrase (combination of setMessage and showMessage)
	bool sayMessage(const sol::this_state& ts, Entity* e, const std::string& msg);

	// Enable or disable the interact prompt on an NPC
	bool enableIntPrompt(const sol::this_state& ts, Entity* e, bool show);

}