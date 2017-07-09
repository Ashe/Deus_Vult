#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics.hpp>

// Enum Shape Type
enum eST {
	Rect, Circle
};

class Widget {
public:
	void release() { if (_subWidget) delete _subWidget; delete _shape; printf("Hud widget deleted safely.\n"); }

	eST getType() const { return _type; } 
	std::map<std::string, float> sizes;

	void draw(sf::RenderWindow*, const sf::Time&, const std::string&, const sf::Vector2f&, const std::map<std::string, sf::Color>&);

	void setShape(sf::Drawable* s, const eST& t) { delete _shape; _type = t; _shape = s; }
	sf::Shape* getShape() { return static_cast<sf::Shape*>(_shape); }

	void setSubWidget(Widget*);

private:
	eST _type;
	sf::Drawable* _shape;
	Widget* _subWidget;
};

#endif // !WIDGET_H

