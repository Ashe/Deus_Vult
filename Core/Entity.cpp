#include "Entity.h"
#include "Component.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Entity Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Entity::~Entity() {
	for (auto& c : components) {
		delete c.second;
	}
}

void Entity::addComp(std::type_index type, Component* c) {
	components[type] = c;
}

void Entity::update(float) {

}

void Entity::render(sf::RenderWindow* window, const sf::Time& dTime) {
	auto graphics = get<GraphicsComponent>();
	if (graphics) {
		graphics->render(window, dTime);
	}
}