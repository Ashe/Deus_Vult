#include "CombatComponent.h"

#include "../Common/Entity.h"

CombatComponent::CombatComponent(Entity* e, sol::table& componentTable) : Component(e) {
	_inCombat = false;

	for (auto &key_value_pair : componentTable) {
		std::string statName = key_value_pair.first.as<std::string>();
		sol::object& value = key_value_pair.second;

		//Value statValue;
		sol::table statTable = value.as<sol::table>();
		sol::object obj = statTable.get<sol::object>("value");
		statType type;
		bool success = false;

		// TEMP
		float flo = 0;
		std::string str = "";
		// END TEMP

		if (obj.get_type() == sol::type::string) {
			//statValue._str = obj.as<std::string>();
			str = obj.as<std::string>();
			type = statType::eString;
			success = true;
		}
		else if ((obj.get_type() == sol::type::number)) {
			//statValue._flo = obj.as<float>();
			flo = obj.as<float>();
			type = statType::eFloat;
			success = true;
		}

		if (success) {
			//_stats.insert(std::make_pair(statName, Stat(statName, type, statValue, drawStyle)));
			_stats.insert(std::make_pair(statName, Stat(statName, type, str, flo)));
		}
	}

	_movement = _owner->get<MovementComponent>();
}

bool CombatComponent::isInCombat() {
	return _inCombat;
}

void CombatComponent::setInCombat(bool inCombat) {
	_inCombat = inCombat;
}

std::map<std::string, Stat>* CombatComponent::getStats() {
	return &_stats;
}
