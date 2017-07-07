#include "GameMap.h"
#include "../ResourceManagers/ResourceManager.h"

void GameMap::loadMap(const std::string& path) {
    _valid = true;
	_gridSize = 100;

    printf("Loading map..\n");

    sol::table mapTable;

    if (ResourceManager::getTable(path)) {
        sol::table resultTable = ResourceManager::getTable(path);
        for (auto key_value_pair : resultTable) {
            _name = key_value_pair.first.as<std::string>();
            sol::object& value = key_value_pair.second;

            mapTable = value.as<sol::table>();
        }
    }
    else {
        _valid = false;
        printf("|- Error: Map data for %s not found.\n", path.c_str());
        return;
    }

    printf("|- Found %s data.\n", _name.c_str());

	printf("-----------------------------\nLoading map %s..\n-----------------------------\n", _name.c_str());

    sol::table geometry = mapTable["Geometry"];
    if (geometry)
        loadGeometry(geometry);
    else {
        printf("|- Error: No Geometry found.\n");
        _valid = false;
    }

	printf("-----------------------------\nMap loaded.\n-----------------------------\n");


}

void GameMap::snapToMap(sf::Vector2f& pos) {
	// This function takes an x value and finds the appropriate y value based
	// on the coordinates in _points

	// Start at the second point, if there is one

	if (pos.x < _leftBound)
		pos.x = _leftBound;

	if (pos.x > _rightBound)
		pos.x = _rightBound;

	const int x = pos.x;

	sf::Vector2i lB, uB;
	{
		int i(1);
		bool endLoop = false;

		while (!endLoop && i < _points.size()) {
			if (x >= _points[i - 1].x && x <= _points[i].x) {
				lB = _points[i - 1];
				uB = _points[i];
				endLoop = true;
			}
			i++;
		}


		if (!endLoop)
			printf("Error: Map::snapToMap failed.\n");
	}
	// y = mx + c
	// c = y - mx
	// Taking uB to work out const
	const float dy = (uB.y - lB.y);
	const float dx = (uB.x - lB.x);
	const float grad = dy / dx;
	const float constant = uB.y - grad * uB.x;

	// Finding y for x:
	pos.y = grad * x + constant;
}

int GameMap::getMidPointX(float x) {
	bool found = false;
	int i = 1;

	int leftMark, rightMark;

	while (!found && i < _marks.getVertexCount()) {
		leftMark = _marks[i - 1].position.x;
		rightMark = _marks[i].position.x;

		if (leftMark <= x && x <= rightMark)
			found = true;
		else
			i++;
	}

	if (found) {
		return (leftMark + rightMark) / 2;
	}
}

void GameMap::render(sf::RenderWindow* window) {
	window->draw(_line);
	window->draw(_marks);
}

bool GameMap::isValid() {
	return _valid;
}

std::string GameMap::getName() {
	return _name;
}

void GameMap::loadGeometry(const sol::table& table) {
    printf("Loading point geometry..\n");

	// Clear any previous data
    _points.clear();
    _line.clear();
	_marks.clear();

	// Setup the type of vertex arrays
	_line = sf::VertexArray(sf::LineStrip);
	_marks = sf::VertexArray(sf::Lines);

    int previousX = NULL;

	// For every coordinate in lua table, parse it
    for (auto coordTable : table) {
        sol::table coord = coordTable.second.as<sol::table>();
        sf::Vector2i point = sf::Vector2i( coord[1], coord[2]);

        printf("|- Found point (%d,%d)..\n", point.x, point.y);

		// Make sure coordinates are from left to right
        if (previousX) {
            if (point.x < previousX) {
                _valid = false;
                printf("| |- Error: point is behind previous point.\n");
            }
            else
                printf("| |- Point is valid.\n");
        }

		// Add coordinate to appropriate arrays
        _points.push_back(point);
        printf("| |- Point pushed into array..\n");

        _line.append(sf::Vector2f(point.x, point.y));
        printf("| |- Point successfully parsed.\n");

        previousX = point.x;
    }

	// Final checks, amount and length
    if (_points.size() < 2) {
        printf("|- Error: Not enough points for a line.\n");
        _valid = false;
    }
    else {
        _length = _points.back().x - _points.front().x;

        if (_length > 0)
            printf("|- Length %d is valid.\n", _length);
        else {
            printf("|- Error: length %d is NOT valid.\n", _length);
            _valid = false;
        }
    }

	// Set bounds
	_leftBound = _points.front().x;
	_rightBound = _points.back().x;

	// Generate the locations for the 'marks'
	for (int i = 0; i <= _length / _gridSize; i++) {
		sf::Vertex mark(sf::Vector2f(_leftBound + i * _gridSize, 0), sf::Color(255, 255, 255, 100));
		snapToMap(mark.position);
		mark.position.y -= 10;
		_marks.append(mark);
		mark.position.y += 20;
		_marks.append(mark);
	}

	// Finish loading
	if (_valid)
		printf("|- Geometry loading successful.\n");
	else
		printf("|- Error: Geometry loading unsuccessful.\n");

}
