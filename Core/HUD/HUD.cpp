#include "HUD.h"

void HUD::setSizes(const sf::Vector2u& size) {
	_windowSize = size;
}

void HUD::render(sf::RenderWindow* window, const sf::Time& dTime) {
	sf::RectangleShape rectangle(sf::Vector2f(120, 50));
	rectangle.setFillColor(sf::Color::Cyan);
	window->draw(rectangle);
}

void HUD::loadStyles(const std::string& path) {
	sol::table hudTable = ResourceManager::getTable(path);
}

void HUD::loadStatsToShow(const sol::table& table) {
	printf("-----------------------------\nLoading Combat System: HUD\n-----------------------------\n");

	for (auto stat : table) {
		const std::string statName = stat.first.as<std::string>();

		StatCustom statToAdd(statName);
		bool success = true;

		sol::table statDisplay = stat.second.as<sol::table>()["display"];
		if (statDisplay) {

			printf("Attempting to register %s..\n", statName.c_str());

			if (statDisplay["style"]) {
				statToAdd.style = statDisplay["style"];
				printf("|- Style set to \"%s\"\n", statToAdd.style.c_str());
			}
			else {
				success = false;
				printf("|- Error: no style listed.\n");
			}

			if (statDisplay["colours"]) {// && statDisplay.get("colours").get_type() == sol::type::table) {
				const sol::table colourTb = statDisplay["colours"];
				for (auto colour : colourTb) {
					const std::string colourName = colour.first.as<std::string>();
					sol::table c = colour.second.as<sol::table>();

					if (c.size() == 4) {
						const int r(c[1]), g(c[2]), b(c[3]), a(c[4]);

						statToAdd.colours[colourName] = sf::Color(c[1], c[2], c[3], c[4]);
						printf("|- Added colour %s: (%d, %d, %d, %d).\n", colourName.c_str(), r, g, b, a);
					}
					else {
						success = false;
						printf("|- Error: Not enough values for colour.\n");
					}
				}
			}
			else {
				success = false;
				printf("|- Error: No colours listed.\n");
			}
		}

		if (success) {
			_stats.push_back(statToAdd);
			printf("|- Successfully registered stat %s.\n", statName.c_str());
		}
	}

		//if (statTable["defaultValue"]) {
		//	if (statTable.get("defaultValue").get_type() == sol::type::number) {

		//	}
		//	else if (statTable.get("defaultValue").get_type() == sol::type::string) {

		//	}
		//}
}
