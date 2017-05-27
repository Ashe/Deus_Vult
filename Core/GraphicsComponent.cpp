#include "GraphicsComponent.h"
#include <sol.hpp>

GraphicsComponent::GraphicsComponent(Entity* e, sol::table& componentTable) : Component(e) {
	auto filenameRef = componentTable["filename"];
	if (filenameRef.valid()) {
		_filename = filenameRef;
		_filename = "Data/" + _filename;

		_spriteWidth = componentTable["size"][1];
		_spriteHeight = componentTable["size"][2];
		_animatedSprite.setOrigin(_spriteWidth / 2, 0);

		if (!setTexture())
			return;

		sol::table animations = componentTable["animations"];
		if (animations) {
			setAnimations(animations);
			_frameTime = componentTable["frameTime"];

			changeAnimation(_animationList.begin()->first);
			auto animRef = componentTable["defaultAnim"];
			if (animRef.valid())
				changeAnimation(animRef);
			else {
				printf("No valid default animation, using %s.\n", _animationList.begin()->first.c_str());
			}
		}
		else {
			_frameTime = 0;
			Animation animation;
			animation.setSpriteSheet(_texture);
			animation.addFrame(sf::IntRect(0, 0, _spriteWidth, _spriteHeight));
			_animationList["default"] = animation;
			changeAnimation("default");
		}

	}
	else {
		printf("Error, GraphicsComponent.filename is not a string!\n");
	}
}

void GraphicsComponent::render(sf::RenderWindow* window, const sf::Time& dTime, const sf::Vector2f& pos) {
	if (_frameTime > 0) {
		_animatedSprite.update(dTime);
	}
	_animatedSprite.setPosition(pos);
	_animatedSprite.setScale((!_flipX * 2 - 1) * 5, 5);
	window->draw(_animatedSprite);
	return;
}

void GraphicsComponent::changeAnimation(const std::string& animName) {
	if (_animationList.count(animName)) {
		_currentAnimation = _animationList[animName];
		_frameTime = _currentAnimation._frameTime;
		_animatedSprite.setFrameTime(sf::milliseconds(_frameTime));
		_animatedSprite.play(_currentAnimation);
		return;
	}

	printf("No animations with %s found.\n", animName.c_str());
}

void GraphicsComponent::setAnimations(sol::table & animationTable) {
	for (auto key_value_pair : animationTable) {
		std::string animationName = key_value_pair.first.as<std::string>();
		sol::object& value = key_value_pair.second;
		sol::table detailsTable = value.as<sol::table>();

		float frameTime = 0;

		if (detailsTable["frameTime"])
			frameTime = detailsTable["frameTime"];

		sol::table frameTable = detailsTable["animation"];

		Animation animation = Animation(frameTime);
		animation.setSpriteSheet(_texture);

		for (int i = frameTable.size(); i > 0; i--) {
			std::pair<sol::object, sol::object> table = frameTable[i];
			sf::IntRect frame;
			sol::table position = table.second.as<sol::table>();
			frame = sf::IntRect( position[1], position[2], _spriteWidth, _spriteHeight);
			animation.addFrame(frame);
		}

		_animationList[animationName] = animation;
	}
}

bool GraphicsComponent::setTexture(){
	if (_texture.loadFromFile(_filename)){
		return true;
	}

	printf("Error, could not load %s!\n", _filename.c_str());
	return false;
}