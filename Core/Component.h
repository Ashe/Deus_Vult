#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component {
public:
	Component(Entity* owner) : _owner(owner) {
		// If a component has no owner, break
		assert(_owner);
	}
	virtual ~Component() {};

	Entity* _owner;
};

#endif