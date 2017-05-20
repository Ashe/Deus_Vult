#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <string>
#include "Scripts.h"
#include "Component.h"
#include "SFML\Graphics.hpp"

class GraphicsComponent : public Component {
public:
	GraphicsComponent(sol::table& componentTable);

	void setImageFilename(const std::string& filename) {
		this->filename = filename;
	}

	std::string getImageFilename() const {
		return filename;
	}

	void render(sf::RenderWindow*, const sf::Time&);

private:
	sf::Texture texture;
	sf::Sprite sprite;
	std::string filename;

	void setTexture();
};

#endif

