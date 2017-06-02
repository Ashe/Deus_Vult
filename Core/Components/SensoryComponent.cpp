#include "SensoryComponent.h"

#include "..\ResourceManagers\EntityList.h"


SensoryComponent::SensoryComponent(Entity* e, sol::table& componentTable) : Component(e) {

	_range = 0;
	if (componentTable["range"]) {
		_range = componentTable["range"];
	}

	TransformComponent* _ownerTransform = _owner->get<TransformComponent>();
	_playerTransform = EntityList::getPlayer()->get<TransformComponent>();
	if (_playerTransform) {
		_playerPosition = _playerTransform->_position;
	}

	_scripts = _owner->get<ScriptComponent>();

	// Add update function to functionlist
	_owner->addUpdateFunction([this](const sf::Time&dTime) {update(dTime); });
}

void SensoryComponent::update(const sf::Time & dTime) {
	if (_playerTransform && _ownerTransform) {
		_playerPosition = _playerTransform->_position;

		bool nowInRange = abs(_playerPosition.x - _ownerTransform->_position.x) < _range;
		if (nowInRange != _inRange) {
			// Call functions to do with range here
			if (!_scripts)
				_scripts = _owner->get<ScriptComponent>();

			if (_scripts) {
				if (nowInRange)
					_scripts->inRange();
				else
					_scripts->outRange();
			}
			_inRange = nowInRange;
		}
		return;
	}

	_ownerTransform = _owner->get<TransformComponent>();
	_playerTransform = EntityList::getPlayer()->get<TransformComponent>();
}

sf::Vector2f SensoryComponent::getPlayerPos() {
	return _playerPosition;
}

bool SensoryComponent::playerInRange()
{
	return _inRange;
}
