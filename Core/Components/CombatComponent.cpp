#include "CombatComponent.h"

#include "../Common/Entity.h"

CombatComponent::CombatComponent(Entity* e, sol::table& componentTable) : Component(e) {
	_inCombat = false;

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