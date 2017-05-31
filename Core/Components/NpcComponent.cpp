#include "NpcComponent.h"
#include <sol.hpp>

#include "..\Common\Entity.h"

NpcComponent::NpcComponent(Entity* e, sol::table& NpcTable) : Component(e) {
	auto phraseRef = NpcTable["phrase"];
	if (phraseRef.valid()) {
		_phrase = phraseRef;
	}
	else {
		printf("Error, NpcComponent.phrase is not a string!\n");
	}

	_facePlayer = false;
	if (NpcTable["facePlayer"]) {
		_facePlayer = NpcTable["facePlayer"];
	}

	_sensoryComponent = _owner->get<SensoryComponent>();
	_transform = _owner->get<TransformComponent>();

	// Add update function to functionlist
	_owner->addUpdateFunction([this](const sf::Time&dTime) {update(dTime);});
}

void NpcComponent::update(const sf::Time& dTime) {
	if (_transform && _sensoryComponent) {
		if (_facePlayer) {
			float playerX = _sensoryComponent->getPlayerPos().x;
				_transform->_flipX = playerX < _transform->_position.x;
		}
		return;
	}
	_sensoryComponent = _owner->get<SensoryComponent>();
	_transform = _owner->get<TransformComponent>();
}

void NpcComponent::setFacePlayer(bool face) {
	_facePlayer = face;
}
