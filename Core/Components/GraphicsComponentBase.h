#ifndef GRAPHICSBASE_H
#define GRAPHICSBASE_H

#include <string>
#include "../Common/Scripts.h"
#include "Component.h"
#include <SFML/Graphics.hpp>

class GraphicsComponentBase : public Component {
public:
	GraphicsComponentBase(Entity* e) : Component(e) {}
	virtual void render(sf::RenderWindow*, const sf::Time&) = 0;
	virtual void changeAnimation(const std::string&) = 0;
	virtual void playAnimation(const std::string&, float) = 0;
	virtual sf::Vector2i getSize() const = 0;
};

#endif // !GRAPHICSBASE_H
