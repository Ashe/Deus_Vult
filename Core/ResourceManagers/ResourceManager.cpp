#include "ResourceManager.h"

std::map<std::string, sf::Image> ResourceManager::_images;
std::map<std::string, sf::Texture> ResourceManager::_textures;
std::map<std::string, sf::Font> ResourceManager::_fonts;


sf::Image* ResourceManager::getImage(const std::string& path) {
	if (!_images.count(path)) {
		sf::Image img;
		if (img.loadFromFile(path)) {
			_images[path] = img;
			printf("| - Loaded image from %s.\n", path.c_str());
		}
		else {
			printf("| - Invalid file path %s.\n", path.c_str());
			return nullptr;
		}
	}

	return &_images[path];
}

sf::Texture* ResourceManager::getTexture(const std::string& path) {
	if (!_textures.count(path)) {
		sf::Texture tex;
		if (!tex.loadFromImage(*getImage(path))) {
			printf("| - Failed loading texture from image: %s\n.", path.c_str());
			return nullptr;
		}
		_textures[path] = tex;
		printf("| - Loaded texture from image: %s.\n", path.c_str());
	}
	return &_textures[path];
}

sf::Font* ResourceManager::getFont(const std::string& path) {
	if (!_fonts.count(path)) {
		sf::Font font;
		if (font.loadFromFile(path)) {
			_fonts[path] = font;
			printf("| - Loaded font from %s.\n", path.c_str());
		}
		else {
			printf("| - Invalid file path %s.\n", path.c_str());
			return nullptr;
		}
	}

	return &_fonts[path];
}

void ResourceManager::releaseData() {
	_images.clear();
	_textures.clear();
	_fonts.clear();
}
