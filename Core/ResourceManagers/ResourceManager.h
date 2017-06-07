#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <assert.h>

class ResourceManager {
public:
	static sf::Image* getImage(const std::string&);
	static sf::Texture* getTexture(const std::string&);
	static sf::Font* getFont(const std::string&);

	static void releaseData();

private:
	static std::map<std::string, sf::Image> _images;
	static std::map<std::string, sf::Texture> _textures;
	static std::map<std::string, sf::Font> _fonts;
};

#endif // !IMAGEMANAGER_H
