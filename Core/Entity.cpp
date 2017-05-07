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

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// LuaHandle Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void LuaEntityHandle::setPhrase(const std::string& phrase) {
	auto npcc = e->get<NpcComponent>();
	if (npcc) {
		npcc->setPhrase(phrase);
	}
	else {
		printf("No NPC Component on entity: %s\n", e->getType().c_str());
	}
}

void LuaEntityHandle::printPhrase() {
	auto npcc = e->get<NpcComponent>();
	if (npcc) {
		printf("%s says: %s", e->getType().c_str(), npcc->getPhrase().c_str());
	}
	else {
		printf("No NPC Component on entity: %s\n", e->getType().c_str());
	}
}