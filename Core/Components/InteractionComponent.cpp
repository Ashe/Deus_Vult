#include "InteractionComponent.h"

#include "..\ResourceManagers\EntityList.h"

InteractionComponent::InteractionComponent(Entity* e, sol::table& componentTable) : Component(e) {
	// Add the render function to the list of functions to render
	_owner->addRenderFunction([this](sf::RenderWindow* window, const sf::Time&dTime) {render(window, dTime); });
}

void InteractionComponent::render(sf::RenderWindow* window, const sf::Time& dTime) {

}