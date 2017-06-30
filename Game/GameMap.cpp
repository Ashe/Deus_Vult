#include "GameMap.h"

#include "../Core/ResourceManagers/ResourceManager.h"

void GameMap::loadMap(const std::string& path) {
    _valid = true;
    printf("Loading map..\n");

    sol::table mapTable;

    if (ResourceManager::getTable(path)) {
        sol::table resultTable = *ResourceManager::getTable(path);
        for (auto key_value_pair : resultTable) {
            printf("Okay\n");
            _name = key_value_pair.first.as<std::string>();
            sol::object& value = key_value_pair.second;

            mapTable = value.as<sol::table>();
        }
    }
    else {
        _valid = false;
        printf("└─ Error: Map data for %s not found.\n", path.c_str());
        return;
    }

    printf("└─ Found %s data.\n", _name.c_str());

	printf("-----------------------------\nLoading map %s.\n-----------------------------\n", _name.c_str());

    sol::table geometry = mapTable["Geometry"];
    if (geometry)
        loadGeometry(geometry);
    else {
        printf("└─ Error: No Geometry found.\n");
        _valid = false;
    }

}

void GameMap::render(sf::RenderWindow* window) {

}

void GameMap::loadGeometry(const sol::table& table) {
    printf("Loading point geometry..\n");

    _points.clear();
    _line.clear();

    int previousX = NULL;

    for (auto coordTable : table) {
        sol::table coord = coordTable.second.as<sol::table>();
        sf::Vector2i point = sf::Vector2i( coord[1], coord[2]);

        printf("├┬─ Found point (%d,%d)..\n", point.x, point.y);

        if (previousX) {
            if (point.x < previousX) {
                _valid = false;
                printf("│├─ Error: point is behind previous point.\n");
            }
            else
                printf("│├─ Point is valid.\n");
        }

        _points.push_back(point);
        printf("│├─ Point pushed into array..\n");

        _line.append(sf::Vertex(sf::Vector2f(point.x, point.y)));
        printf("├┴─ Point successfully parsed.\n");

        previousX = point.x;
    }

    if (_points.size() < 2) {
        printf("├─ Error: Not enough points for a line.\n");
        _valid = false;
    }
    else {
        _length = _points.back().x - _points.front().x;

        if (_length > 0)
            printf("├─ Length %d is valid.\n", _length);
        else {
            printf("├─ Error: length %d is NOT valid.", _length);
            _valid = false;
        }
    }

    printf("└─ Geometry loading successful.\n");

}
