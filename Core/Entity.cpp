#include "Entity.h"
#include "Component.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Entity Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Entity::~Entity() {
	for (auto& c : _components) {
		delete c.second;
	}
}

void Entity::addComp(std::type_index type, Component* c) {
	_components[type] = c;
}

void Entity::update(float) {

}

void Entity::render(sf::RenderWindow* window, const sf::Time& dTime) {
	auto graphics = get<GraphicsComponent>();
	auto position = get<PositionComponent>();
	if (graphics && position)
		graphics->render(window, dTime, position->_position);
}