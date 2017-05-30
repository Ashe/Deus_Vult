#include "ResourceManager.h"

std::map<std::string, sf::Image> ResourceManager::_images;
std::map<std::string, sf::Texture> ResourceManager::_textures;

sf::Image* ResourceManager::getImg(const std::string& path) {
	if (!_images.count(path)) {
		sf::Image img;
		if (img.loadFromFile(path)) {
			_images[path] = img;
			printf("| - Loaded image from %s.\n", path.c_str());
		}
		else {
			printf("Invalid file path %s.\n", path.c_str());
			assert(false);
			return NULL;
		}
	}

	return &_images[path];
}

sf::Texture* ResourceManager::getTex(const std::string& path) {
	if (!_textures.count(path)) {
		sf::Texture tex;
		if (!tex.loadFromImage(*getImg(path))) {
			printf("Failed loading texture from %s\n.", path.c_str());
			assert(false);
			return NULL;
		}
		_textures[path] = tex;
		printf("| - Loaded texture from %s.\n", path.c_str());
	}
	return &_textures[path];
}

void ResourceManager::releaseData() {
	_images.clear();
	_textures.clear();
}