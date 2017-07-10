#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics.hpp>

// Enum Shape Type
enum eST {
	Nothing, Rect, Circle
};

class Widget {
public:
	Widget();
	void release() { for (auto &w : _subWidget) w.release();  delete _shape; printf("Hud widget deleted safely.\n"); }

	eST getType() const { return _type; } 
	std::map<std::string, float> sizes;

	void draw(sf::RenderWindow*, const sf::Time&, const std::string&, const sf::Vector2f&, const std::map<std::string, sf::Color>&);

	void setShape(sf::Drawable* s, const eST& t) { delete _shape; _type = t; _shape = s; }
	sf::Shape* getShape() { return static_cast<sf::Shape*>(_shape); }

	void initialiseDrawing();
	void setSubWidget(Widget);

private:
	eST _type = eST::Nothing;
	sf::Drawable* _shape;
	std::vector<Widget> _subWidget;

	bool readyToDraw;
	sf::Vector2f _start, _end;
};

#endif // !WIDGET_H

