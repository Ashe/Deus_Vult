#include "HUD.h"

HUD::~HUD() {
	/*for (auto &s : _allStyles)
		for (auto &w : s)
			w.release();*/

	for (auto &w : _allStyles)
		w.release();
}

void HUD::setSizes(const sf::Vector2u& size) {
	_windowSize = size;

	for (auto &&w : _allStyles) {
		w.initialiseDrawing();
	}
}

void HUD::render(sf::RenderWindow* window, const sf::Time& dTime) {
	sf::RectangleShape rectangle(sf::Vector2f(120, 50));
	rectangle.setFillColor(sf::Color::Cyan);

	for (auto &&w : _allStyles) {
		w.draw(window, dTime, "topLeft", sf::Vector2f(510, 30), std::map<std::string, sf::Color>());
	}

}

void HUD::loadHUD(const std::string& path) {

	printf("-----------------------------\nLoading HUD..\n-----------------------------\n");


	sol::table hudTable = ResourceManager::getTable(path);
	for (auto &style : hudTable) {
		const std::string styleName = style.first.as<std::string>();
		//std::vector<Widget> styleWidgets = loadStyle(style.second.as<sol::table>());
		Widget styleWidget = loadStyle(style.second.as<sol::table>());

		//if (styleWidgets.size() > 0) {
		if (styleWidget.getType() != eST::Nothing) {

			_allStyles.push_back(styleWidget);
			_styles[styleName] = styleWidget;
			printf("|- Loaded style: %s.\n", styleName.c_str());
		}
	}

	printf("-----------------------------\nHUD loaded.\n-----------------------------\n");

}

void HUD::loadStatsToShow(const sol::table& table) {
	printf("-----------------------------\nLoading Combat System: HUD\n-----------------------------\n");

	for (auto &stat : table) {
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
				for (auto &colour : colourTb) {
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
}

Widget HUD::loadStyle(const sol::table& stb) {

	std::map<int, Widget> layers;
	int highestLayer(-1);

	for (auto &shape : stb) {
		const std::string shapeName = shape.first.as<std::string>();
		printf("Loading shape %s..\n", shapeName.c_str());
		const sol::table details = shape.second.as<sol::table>();
		bool success = true;
		int layer;
		Widget widget;

		if (details["layer"]) {
			layer = abs(details["layer"].get<int>());
		}
		else {
			success = false;
			printf("|- Error: No layer given.\n");
		}

		if (details["shape"].valid() && success) {
			const std::string shapeType = details["shape"];

			// Rectangles
			if (shapeType == "rect" || shapeType == "rectangle") {
				loadRect(details, widget, success);
			}

			// Circles
			else if (shapeType == "circle" || shapeType == "elipse" || shapeType == "oval") {
				loadCircle(details, widget, success);
			}

			// If no shape found, report error
			else {
				success = false;
				printf("|- Error: Unrecognised shape type.\n");
			}

			// When the shape has been created, do the colours
			// TODO: CROSS REFERENCE WITH BACK COLOURS
			if (details["colours"]) {
				loadColours(details["colours"], widget, success);
			}
			else {
				success = false;
				printf("|- Error: No colours given.\n");
			}

		}
		else {
			success = false;
			printf("|- Error: No valid shape type given.\n");
		}

		// When done, if successful, prep the widget
		if (success) {
			if (layers.count(layer)) {
				success = false;
				printf("|- Error: 2 shapes are being drawn to same layer.\n");
			}
			// If its okay, store in a temporary map of layers for sorting
			else {
				if (layer > highestLayer)
					highestLayer = layer;

				layers[layer] = widget;
			}
		}
	}

	// After all the shapes are processed, sort
	for (int i = highestLayer; i > 0; i--) {
		if (layers.count(i)) {
			layers[i - 1].setSubWidget(layers[i]);
			//style.push_back(layers[i]);
			printf("|- Registered on layer %d.\n", i);
		}
	}

	if (layers.size() > 0)
		return layers[0];

	return Widget();

}

void HUD::loadRect(const sol::table& table, Widget& widget, bool& success) {

	sol::table tb = table;
	sf::RectangleShape rect;
	widget.setShape(new sf::RectangleShape(), eST::Rect);

	// Sizing
	if (tb["widthStart"]) {
		sol::object value = tb["widthStart"];
		if (value.get_type() == sol::type::number)
			widget.sizes["widthStart"] = value.as<float>() / 100;
	}
	else
		widget.sizes["widthStart"] = 0;

	if (tb["widthEnd"]) {
		sol::object value = tb["widthEnd"];
		if (value.get_type() == sol::type::number)
			widget.sizes["widthEnd"] = value.as<float>() / 100;
	}
	else
		widget.sizes["widthEnd"] = 1;

	if (tb["heightStart"]) {
		sol::object value = tb["heightStart"];
		if (value.get_type() == sol::type::number)
			widget.sizes["heightStart"] = value.as<float>() / 100;
	}
	else
		widget.sizes["heightStart"] = 0;

	if (tb["heightEnd"]) {
		sol::object value = tb["heightEnd"];
		if (value.get_type() == sol::type::number)
			widget.sizes["heightEnd"] = value.as<float>() / 100;
	}
	else
		widget.sizes["heightEnd"] = 1;

	// Thickness
	if (tb["outlineThickness"]) {
		widget.getShape()->setOutlineThickness(tb["outlineThickness"]);
	}

}

void HUD::loadCircle(const sol::table& tb, Widget& widget, bool& success) {
	success = false;
}

void HUD::loadColours(const sol::table& tb, Widget& widget, bool& success) {
	sf::Shape* const shape = widget.getShape();

	if (tb["fill"].valid()) {
		const sol::table fillTable = tb["fill"];
		if (fillTable["default"]) {
			const sol::table c = fillTable["default"];
			shape->setFillColor(sf::Color(c[1], c[2], c[3], c[4]));
		}
		else {
			success = false;
			printf("|- Error: Fill colour doesn't give a colour.\n");
		}
	}
	else {
		success = false;
		printf("|- Error: No fill colour given.\n");
	}

	if (tb["outline"].valid()) {
		const sol::table outlineTable = tb["outline"];
		if (outlineTable["default"]) {
			const sol::table c = outlineTable["default"];
			shape->setOutlineColor(sf::Color(c[1], c[2], c[3], c[4]));
		}
		else {
			printf("|- Minor Error: Outline colour doesn't give a colour.\n");
		}
	}

}
