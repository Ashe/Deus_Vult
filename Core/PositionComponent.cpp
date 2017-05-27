#include "PositionComponent.h"

PositionComponent::PositionComponent(Entity* e, sol::table& componentTable) : Component(e) {
	_position.x = componentTable[1];
	_position.y = componentTable[2];
}