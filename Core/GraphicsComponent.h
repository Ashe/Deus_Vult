#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <string>
#include "Scripts.h"
#include "Component.h"
#include "SFML\Graphics.hpp"

#include "AnimatedSprite.hpp"
#include "TransformComponent.h"

class GraphicsComponent : public Component {
public:
	GraphicsComponent(Entity* e, sol::table& componentTable);

	void setImageFilename(const std::string& filename) {
		this->_filename = filename;
		setTexture();
	}

	std::string getImageFilename() const {
		return _filename;
	}
	void render(sf::RenderWindow*, const sf::Time&);

	void changeAnimation(const std::string&);

private:
	// Sprite details
	std::string _filename;
	sf::Texture _texture;
	int _spriteWidth = 32;
	int _spriteHeight = 32;

	// Animations
	AnimatedSprite _animatedSprite;
	Animation _currentAnimation = Animation();
	std::map<std::string, Animation> _animationList;
	int _frameTime = 0;

	sf::Color _outline;
	float _outlineThickness;

	TransformComponent* _transform;

	bool setTexture();
	void setAnimations(sol::table&);

};

#endif