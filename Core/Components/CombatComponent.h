#ifndef COMBATCOMPONENT_H
#define COMBATCOMPONENT_H

#include <string>
#include "../Common/Scripts.h" 
#include "Component.h"

#include "MovementComponent.h"

#include "../../Game/Stats.h"

class CombatComponent : public Component {
public:
	CombatComponent(Entity* e, sol::table& componentTable);

	bool isInCombat();
	void toggleCombat();

private:
	MovementComponent* _movement;
	bool _inCombat;

	std::map<std::string, Stat> _stats;
};

#endif 