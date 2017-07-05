#include "HUD.h"

void HUD::render(sf::RenderWindow* window, const sf::Time& dTime) {
	sf::RectangleShape rectangle(sf::Vector2f(120, 50));
	rectangle.setFillColor(sf::Color::Cyan);
	window->draw(rectangle);
}
