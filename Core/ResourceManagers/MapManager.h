#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "../Common/GameMap.h"

class MapManager {
public:
	static GameMap* getCurrentMap();
	static GameMap* loadMap(const std::string& path);
	static GameMap* changeMap(const std::string& pathOrName);

	static void clearMaps();

private:
	static GameMap* _currentMap;

	// Map NAME to PATH
	static std::map<std::string, std::string> _mapNames;

	// Map PATH to MAP
	static std::map<std::string, GameMap> _maps;
};

#endif