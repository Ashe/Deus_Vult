#include "TransformComponent.h"

#include "../ResourceManagers/MapManager.h"

TransformComponent::TransformComponent(Entity* e, sol::table& componentTable) : Component(e) {
    _position = sf::Vector2f(0, 0);
	if (componentTable["position"]) {
		if (componentTable["position"][1])
			_position.x = componentTable["position"][1];

		if (componentTable["position"][2])
			_position.y = componentTable["position"][2];
	}

	// If there's a map, snap to it for convenience
	GameMap* map= MapManager::getCurrentMap();
	if (map)
		map->snapToMap(_position);

        _scale = sf::Vector2f(1, 1);
	if (componentTable["scale"]) {
		if (componentTable["scale"][1])
			_scale.x = componentTable["scale"][1];
		if (componentTable["scale"][2])
			_scale.y = componentTable["scale"][2];
	}

	if (componentTable["rotation"])
		_rotation = componentTable["rotation"];
	else
		_rotation = 0;

	if (componentTable["flipX"])
		_flipX = componentTable["flipX"];
	else
		_flipX = false;

	if (componentTable["flipY"])
		_flipY = componentTable["flipY"];
	else
		_flipY = false;
}
