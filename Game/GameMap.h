#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "../Core/Common/Scripts.h"
#include <SFML/Graphics.hpp>

class GameMap {
public:
    void loadMap(const std::string&);

    void render(sf::RenderWindow*);

private:
    bool _valid;
    std::string _name;
    int _length;

    sf::VertexArray _line;
    std::vector<sf::Vector2i> _points;

    void loadGeometry (const sol::table&);

};
#endif
