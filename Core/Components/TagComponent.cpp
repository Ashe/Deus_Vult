#include "TagComponent.h"

#include "../ResourceManagers/EntityList.h"

TagComponent::TagComponent(Entity* e, sol::table& componentTable) : Component(e) {
	for (auto table : componentTable) {
		const std::string tag = table.second.as<std::string>();
		_tags.push_back(tag);
		EntityList::addEntityWithTag(e, tag);
	}
}