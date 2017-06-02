#include "InteractionComponent.h"

#include "..\ResourceManagers\EntityList.h"

InteractionComponent::InteractionComponent(Entity* e, sol::table& componentTable) : Component(e) {

	_text.setString("E");
	_text.setFont(*ResourceManager::getFont("Data/common/fonts/belgrano/regular.ttf"));
	_text.setOrigin(_text.getCharacterSize() / 3, _text.getCharacterSize() / 2);

	_spriteHeight = _owner->get<GraphicsComponent>()->getSize().y;
	_transform = _owner->get<TransformComponent>();
	_sensor = _owner->get<SensoryComponent>();

	// Add the render function to the list of functions to render
	_owner->addRenderFunction([this](sf::RenderWindow* window, const sf::Time&dTime) {render(window, dTime); });
}

void InteractionComponent::render(sf::RenderWindow* window, const sf::Time& dTime) {
	if (EntityList::getClosestInteractive() == _owner) {
		if (_transform && _sensor) {
			if (_sensor->playerInRange()) {
				_text.setPosition(_owner->get<TransformComponent>()->_position);
				_text.move(0, - 2 * (_spriteHeight * _transform->_scale.y / 3));
				window->draw(_text);
				return;
			}
		}

		_spriteHeight = _owner->get<GraphicsComponent>()->getSize().y;
		_transform = _owner->get<TransformComponent>();
		_sensor = _owner->get<SensoryComponent>();
	}
}