#include "NpcComponent.h"
#include <iostream>
#include <sol.hpp>

NpcComponent::NpcComponent(sol::table& NpcTable) {
	auto phraseRef = NpcTable["phrase"];
	if (phraseRef.valid()) {
		phrase = phraseRef;
	}
	else {
		std::cout << "Error, NpcComponent.phrase is not a string!" << std::endl;
	}
}