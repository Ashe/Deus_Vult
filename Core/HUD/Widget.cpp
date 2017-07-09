#include "Widget.h"

void Widget::draw(sf::RenderWindow* window, const sf::Time& dTime, const std::string& anchor, const sf::Vector2f& size, const std::map<std::string, sf::Color>& colours) {
	switch (_type) {
	case eST::Rect: {
		sf::RectangleShape* rect = static_cast<sf::RectangleShape*>(_shape);

		float widthStart = 0;
		if (sizes["widthStart"])
			widthStart = sizes["widthStart"];

		float widthEnd = 1;
		if (sizes["widthEnd"])
			widthEnd = sizes["widthEnd"];

		float heightStart = 0;
		if (sizes["heightStart"])
			heightStart = sizes["heightStart"];

		float heightEnd = 1;
		if (sizes["heightEnd"])
			heightEnd = sizes["heightEnd"];

		rect->setPosition(0 + size.x * widthStart, 0 + size.y * heightStart);
		rect->setSize(sf::Vector2f((widthEnd - widthStart) * size.x, (heightEnd - heightStart) * size.y));


		break; }
	case eST::Circle: {
		break; }
	}

	window->draw(*_shape);
}

void Widget::setSubWidget(Widget* w) {
	_subWidget = w;
}
