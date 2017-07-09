#include "Widget.h"

Widget::Widget() {
	readyToDraw = false;
}

void Widget::draw(sf::RenderWindow* window, const sf::Time& dTime, const std::string& anchor, const sf::Vector2f& size, const std::map<std::string, sf::Color>& colours) {
	switch (_type) {
	case eST::Rect: {
		sf::RectangleShape* rect = static_cast<sf::RectangleShape*>(_shape);

		if (readyToDraw) {
			rect->setPosition(0 + size.x * _start.x, 0 + size.y * _start.y);
			rect->setSize(sf::Vector2f((_end.x - _start.x) * size.x, (_end.y - _start.y) * size.y));
		}
		else
			initialiseDrawing();

		break; }
	case eST::Circle: {
		break; }
	}

	window->draw(*_shape);
	for (auto &&w : _subWidget)
		w.draw(window, dTime, anchor, size, colours);
}

void Widget::setSubWidget(Widget w) {
	_subWidget.clear();
	_subWidget.push_back(w);
}

void Widget::initialiseDrawing() {

	_start.x = 0;
	if (sizes["widthStart"])
		_start.x = sizes["widthStart"];

	_end.x = 1;
	if (sizes["widthEnd"])
		_end.x = sizes["widthEnd"];

	_start.y = 0;
	if (sizes["heightStart"])
		_start.y = sizes["heightStart"];

	_end.y = 1;
	if (sizes["heightEnd"])
		_end.y = sizes["heightEnd"];

	readyToDraw = true;

	for (auto &&w : _subWidget)
		w.initialiseDrawing();
}
