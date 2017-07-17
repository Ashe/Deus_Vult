#include "ResourceManager.h"

sol::state* ResourceManager::_lua;
std::map<std::string, sol::table> ResourceManager::_tables;
std::map<std::string, sf::Image> ResourceManager::_images;
std::map<std::string, sf::Texture> ResourceManager::_textures;
std::map<std::string, sf::Font> ResourceManager::_fonts;

sol::table ResourceManager::getTable(const std::string& path) {

    if (!_tables.count(path)) {
		sol::protected_function_result result = _lua->do_file("Data/" + path);
		if (!result.valid()) {
			sol::error err = result;
			sol::call_status status = result.status();
			printf("|- Error: %s, details: .%s\n", sol::to_string(status).c_str(), err.what());
			return sol::table();
		}
		_tables[path] = result;
        printf("|- Loaded table from %s.\n", path.c_str());
    }

    return _tables[path];
}

sf::Image* ResourceManager::getImage(const std::string& path) {
	if (!_images.count(path)) {
		sf::Image img;
		if (img.loadFromFile("Data/" + path)) {
			_images[path] = img;
			printf("|- Loaded image from %s.\n", path.c_str());
		}
		else {
			printf("|- Invalid file path %s.\n", path.c_str());
			return nullptr;
		}
	}

	return &_images[path];
}

sf::Texture* ResourceManager::getTexture(const std::string& path) {
	if (!_textures.count(path)) {
		sf::Texture tex;
		if (!tex.loadFromImage(*getImage(path))) {
			printf("|- Failed loading texture from image: %s\n.", path.c_str());
			return nullptr;
		}
		_textures[path] = tex;
		printf("|- Loaded texture from image: %s.\n", path.c_str());
	}
	return &_textures[path];
}

sf::Font* ResourceManager::getFont(const std::string& path) {
	if (!_fonts.count(path)) {
		sf::Font font;
		if (font.loadFromFile("Data/" + path)) {
			_fonts[path] = font;
			printf("|- Loaded font from %s.\n", path.c_str());
		}
		else {
			printf("|- Invalid file path %s.\n", path.c_str());
			return nullptr;
		}
	}

	return &_fonts[path];
}

void ResourceManager::setLua(sol::state& lua) {
    _lua = &lua;
}

void ResourceManager::releaseData() {
	_images.clear();
	_textures.clear();
	_fonts.clear();
    _tables.clear();
}
