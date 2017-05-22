#include "PositionComponent.h"

PositionComponent::PositionComponent(sol::table& componentTable) {
	_position.x = componentTable[1];
	_position.y = componentTable[2];
}