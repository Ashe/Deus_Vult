#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "SFML\Graphics.hpp"
#include <assert.h>

class ResourceManager {
public:
	static sf::Image* getImg(const std::string&);
	static sf::Texture* getTex(const std::string&);
	static void releaseData();

private:
	static std::map<std::string, sf::Image> _images;
	static std::map<std::string, sf::Texture> _textures;
};

#endif // !IMAGEMANAGER_H
