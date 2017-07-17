#include "InteractionComponent.h"

#include "../ResourceManagers/EntityList.h"

InteractionComponent::InteractionComponent(Entity* e, sol::table& componentTable) : Component(e) {

	_showPrompt = false;
	if (componentTable["showPrompt"])
		_showPrompt = componentTable["showPrompt"];

	_text.setString("E");
	_text.setFont(*ResourceManager::getFont("common/fonts/belgrano/regular.ttf"));
	_text.setOrigin(_text.getCharacterSize() / 3, _text.getCharacterSize() / 2);

	_transform = _owner->get<TransformComponent>();
	_sensor = _owner->get<SensoryComponent>();

	// Add the render function to the list of functions to render
	_owner->addRenderFunction([this](sf::RenderWindow* window, const sf::Time&dTime) {render(window, dTime); });
}

void InteractionComponent::render(sf::RenderWindow* window, const sf::Time& dTime) {
	if (_showPrompt && _transform && _sensor && EntityList::getClosestInteractive() == _owner) {
		if (_sensor->playerInRange()) {
			_text.setPosition(_transform->_position);
			_text.move(0, -_owner->getSize().y / 2);
			window->draw(_text);
			return;
		}

		_transform = _owner->get<TransformComponent>();
		_sensor = _owner->get<SensoryComponent>();
	}
}

void InteractionComponent::setShowInteractPrompt(bool show) {
	_showPrompt = show;
}
