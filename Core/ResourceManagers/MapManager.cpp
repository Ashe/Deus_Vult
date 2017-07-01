#include "MapManager.h"

GameMap* MapManager::_currentMap;
std::map<std::string, GameMap> MapManager::_maps;
std::map<std::string, std::string> MapManager::_mapNames;

GameMap* MapManager::getCurrentMap() {
	return _currentMap;
}

GameMap* MapManager::loadMap(const std::string& path) {
	GameMap tempMap;
	tempMap.loadMap(path);

	if (tempMap.isValid()) {
		_maps[path] = tempMap;
		_mapNames[tempMap.getName()] = path;

		return &_maps[path];
	}

	return nullptr;
}

GameMap* MapManager::changeMap(const std::string& pathOrName) {
	// If its a name
	if (_mapNames.count(pathOrName) && _maps.count(_mapNames[pathOrName])) {
		_currentMap = &_maps[_mapNames[pathOrName]];
		return _currentMap;
	}

	// If its a path
	if (_maps.count(pathOrName)) {
		_currentMap = &_maps[pathOrName];
		return _currentMap;
	}

	// Last resort: Try and load it
	_currentMap = loadMap(pathOrName);
	return _currentMap;
}

void MapManager::clearMaps() {
	_maps.clear();
}
