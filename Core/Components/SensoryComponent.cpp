#include "SensoryComponent.h"

#include "..\ResourceManagers\EntityList.h"


SensoryComponent::SensoryComponent(Entity * e, sol::table & componentTable) : Component(e) {
	_playerPosition = EntityList::getPlayer()->get<TransformComponent>();
}

sf::Vector2f SensoryComponent::getPlayerPos() {
	if (_playerPosition)
		return _playerPosition->_position;
	
	_playerPosition = EntityList::getPlayer()->get<TransformComponent>();
		return _playerPosition->_position;
}
