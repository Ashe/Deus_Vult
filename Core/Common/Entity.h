#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <string>
#include <typeindex>

#include "..\Common\Scripts.h"

#include "..\Components\GraphicsComponent.h"
#include "..\Components\OutlineComponent.h"
#include "..\Components\SensoryComponent.h"
#include "..\Components\TransformComponent.h"
#include "..\Components\MovementComponent.h"
#include "..\Components\NpcComponent.h"
#include "..\Components\ControllerComponent.h"

// Forward declaration
class Component;

// Main Entity
class Entity {
public:

	~Entity();

	void addComp(std::type_index type, Component* c);

	template <typename T>
	T* get() {
		auto it = _components.find(std::type_index(typeid(T)));
		if (it != _components.end()) {
			return dynamic_cast<T*>(it->second);
		}
		return nullptr;
	}

	void setType(const std::string& type) {
		this->_type = type;
	}

	std::string getType() const {
		return _type;
	}

	void update(const sf::Time&);
	void render(sf::RenderWindow*, const sf::Time&);
	void addUpdateFunction(std::function<void(const sf::Time&)>);
	void addRenderFunction(std::function<void(sf::RenderWindow*, const sf::Time&)>);

private:
	std::string _type;
	std::map<std::type_index, Component*> _components;

	std::vector<std::function<void(const sf::Time&)>> _updateFunctions;
	std::vector<std::function<void(sf::RenderWindow*, const sf::Time&)>> _renderFunctions;
};

template <typename T>
static void addComponent(Entity* e, sol::table& componentTable) {
	e->addComp(std::type_index(typeid(T)), new T(e, componentTable));
}
#endif