#include "TransformComponent.h"

TransformComponent::TransformComponent(Entity* e, sol::table& componentTable) : Component(e) {
	if (componentTable["position"]) {
		if (componentTable["position"][1])
			_position.x = componentTable["position"][1];
		else
			_position.x = 0;

		if (componentTable["position"][2])
			_position.y = componentTable["position"][2];
		else
			_position.y = 0;
	}

	if (componentTable["scale"]) {
		if (componentTable["scale"][1])
			_scale.x = componentTable["scale"][1];
		else
			_scale.x = 1;
		if (componentTable["scale"][2])
			_scale.y = componentTable["scale"][2];
		else
			_scale.y = 1;
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