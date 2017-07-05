#include "CombatComponent.h"

#include "../Common/Entity.h"

CombatComponent::CombatComponent(Entity* e, sol::table& componentTable) : Component(e) {
	_inCombat = false;

	for (auto key_value_pair : componentTable) {
		std::string statName = key_value_pair.first.as<std::string>();
		sol::object& value = key_value_pair.second;

		//Value statValue;
		sol::table statTable = value.as<sol::table>();
		sol::object obj = statTable.get<sol::object>("value");
		std::string type;
		bool success = false;

		std::string drawStyle;
		auto drawRef = statTable["drawStyle"];
		if (drawRef.valid())
			drawStyle = drawRef;

		// TEMP
		float flo;
		std::string str;
		// END TEMP

		if (obj.get_type() == sol::type::string) {
			//statValue._str = obj.as<std::string>();
			str = obj.as<std::string>();
			type = typeid(std::string).name();
			success = true;
		}
		else if ((obj.get_type() == sol::type::number)) {
			//statValue._flo = obj.as<float>();
			flo = obj.as<float>();
			type = typeid(float).name();
			success = true;
		}

		if (success) {
			//_stats.insert(std::make_pair(statName, Stat(statName, type, statValue, drawStyle)));
			_stats.insert(std::make_pair(statName, Stat(statName, type, str, flo, drawStyle)));
		}

	}

	_movement = _owner->get<MovementComponent>();
}

bool CombatComponent::isInCombat() {
	return _inCombat;
}

void CombatComponent::toggleCombat() {

	if (!_movement)
		_movement = _owner->get<MovementComponent>();

	if (!_inCombat) {
		_inCombat = true;

		if (_movement) {
			_movement->setLockMovement(true);
			_movement->moveToMidpoint();
		}
	}
	else { // not in combat
		_inCombat = false;
		if (_movement) {
			_movement->setLockMovement(false);
		}
	}

}