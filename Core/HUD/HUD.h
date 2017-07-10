#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include "../ResourceManagers/ResourceManager.h"

struct StatCustom {
	StatCustom(const std::string& n) : name(n) {}

	const std::string name;
	std::string style;
	std::map<std::string, sf::Color> colours;
};

class HUD {
public:

	~HUD();

	void setSizes(const sf::Vector2u&);
	void render(sf::RenderWindow*, const sf::Time&);

	void loadHUD(const std::string&);
	void loadStatsToShow(const sol::table&);

private:
	sf::Vector2u _windowSize;
};

#endif // !define HUD_H
