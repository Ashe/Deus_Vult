#include "GraphicsComponent.h"
#include <sol.hpp>

GraphicsComponent::GraphicsComponent(sol::table& componentTable) {
	auto filenameRef = componentTable["filename"];
	if (filenameRef.valid()) {
		_filename = filenameRef;
		_filename = "Data/" + _filename;

		_spriteWidth = componentTable["size"][1];
		_spriteHeight = componentTable["size"][2];

		if (!setTexture())
			return;

		sol::table animations = componentTable["animations"];
		if (animations) {
			setAnimations(animations);
			_frameTime = componentTable["frameTime"];

			auto animRef = componentTable["defaultAnim"];
			if (animRef.valid())
				changeAnimation(animRef);
			else
				printf("%s is not a valid string!", animRef);
		}
	}
	else {
		printf("Error, GraphicsComponent.filename is not a string!\n");
	}
}

void GraphicsComponent::render(sf::RenderWindow* window, const sf::Time& dTime) {
	if (_frameTime > 0) {
		_animatedSprite.update(dTime);
		window->draw(_animatedSprite);
		return;
	}

	window->draw(_sprite);
}

void GraphicsComponent::changeAnimation(const std::string& animName) {
	for (AnimWrapper animation : _animationList) {
		if (animation.name == animName) {
			_currentAnimation = animation.anim;
			_animatedSprite.setFrameTime(sf::milliseconds(_frameTime));
			_animatedSprite.play(_currentAnimation);
			return;
		}
	}

	printf("No animations with %s found.", animName.c_str());
}

void GraphicsComponent::setAnimations(sol::table & animationTable) {
	for (auto key_value_pair : animationTable) {
		std::string animationName = key_value_pair.first.as<std::string>();
		sol::object& value = key_value_pair.second;
		sol::table frameTable = value.as<sol::table>();

		Animation animation;
		animation.setSpriteSheet(_texture);

		for (auto table : frameTable) {
			sf::IntRect frame;
			sol::table position = table.second.as<sol::table>();
			frame = sf::IntRect( position[1], position[2], _spriteWidth, _spriteHeight);
			animation.addFrame(frame);
		}

		_animationList.push_back(AnimWrapper(animationName, animation));
	}
}

bool GraphicsComponent::setTexture(){
	if (_texture.loadFromFile(_filename)){
		_sprite.setTexture(_texture);
		return true;
	}

	printf("Error, could not load %s!\n", _filename.c_str());
	return false;
}