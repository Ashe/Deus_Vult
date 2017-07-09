#include "Entity.h"
#include "../Components/Component.h"

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

void Entity::init() {
	for (auto &function : _initFunctions)
		function();
}

void Entity::interact() {
	for (auto &function : _interactFunctions)
		function();
}

void Entity::update(const sf::Time& dTime) {
	for (auto &function : _updateFunctions)
            function(dTime);
}

void Entity::render(sf::RenderWindow* window, const sf::Time& dTime) {
	// TODO: THIS FUNCTION MUST BE FIXED FOR EFFICIENCY

	for (auto &function : _renderFunctions)
		function(window, dTime);

	auto interact = get<InteractionComponent>();
	if (interact)
		interact->render(window, dTime);
}

void Entity::addInitFunction(std::function<void()> func) {
	_initFunctions.push_back(func);
}

void Entity::addInteractFunction(std::function<void()> func) {
	_interactFunctions.push_back(func);
}

void Entity::addUpdateFunction(std::function<void(const sf::Time&)> func) {
	_updateFunctions.push_back(func);
}

void Entity::addRenderFunction(std::function<void(sf::RenderWindow*, const sf::Time&)> func) {
	_renderFunctions.push_back(func);
}

sf::Vector2i Entity::getSize()
{
	if (get<SpineComponent>())
		return get<SpineComponent>()->getSize();

	if (get<SpriteComponent>()) {
		const auto sprite = get<SpriteComponent>()->getSize();
		if (get<TransformComponent>()) {
			const auto trans = get<TransformComponent>()->_scale;
			return sf::Vector2i(sprite.x * trans.x, sprite.y * trans.y);
		}
		return sf::Vector2i(sprite.x, sprite.y);
	}

	return sf::Vector2i();
}
