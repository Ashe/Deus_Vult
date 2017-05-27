#include "NpcComponent.h"
#include <sol.hpp>

NpcComponent::NpcComponent(Entity* e, sol::table& NpcTable) : Component(e) {
	auto phraseRef = NpcTable["phrase"];
	if (phraseRef.valid()) {
		_phrase = phraseRef;
	}
	else {
		printf("Error, NpcComponent.phrase is not a string!\n");
	}
}