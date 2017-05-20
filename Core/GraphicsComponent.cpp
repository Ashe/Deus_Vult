#include "GraphicsComponent.h"
#include <sol.hpp>

GraphicsComponent::GraphicsComponent(sol::table& componentTable) {
	auto filenameRef = componentTable["filename"];
	if (filenameRef.valid()) {
		filename = filenameRef;
		filename = "Data/" + filename;
		setTexture();
	}
	else {
		printf("Error, GraphicsComponent.filename is not a string!\n");
	}
}

void GraphicsComponent::render(sf::RenderWindow* window, const sf::Time& dTime) {
	window->draw(sprite);
}

void GraphicsComponent::setTexture(){
	if (texture.loadFromFile(filename)){
		sprite.setTexture(texture);
		return;
	}

	printf("Error, could not load %s!\n", filename.c_str());
}