#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <SFML/Graphics.hpp>
#include "Scripts.h"

class GameMap {
public:
    void loadMap(const std::string&);
	void snapToMap(sf::Vector2f&);

    void render(sf::RenderWindow*);

	bool isValid();
	std::string getName();

private:
    bool _valid;
    std::string _name;
    int _length;
	int _leftBound;
	int _rightBound;

    sf::VertexArray _line;
	sf::VertexArray _marks;

    std::vector<sf::Vector2i> _points;

    void loadGeometry (const sol::table&);

};
#endif
