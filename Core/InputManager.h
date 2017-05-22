#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "SFML\Graphics.hpp"


class InputManager {

public:
	typedef void(*voidFunction)();
	struct FunctionPair {
		FunctionPair() {}
		FunctionPair(voidFunction kd, voidFunction kr)
			: _keyDown(kd), _keyRelease(kr) {}

		voidFunction _keyDown = NULL;
		voidFunction _keyRelease = NULL;
	};

	std::map<sf::Keyboard::Key, std::string> _keys;
	std::map<sf::Keyboard::Key, bool> _keyStatus;
	std::map<std::string, FunctionPair> _actions;

	void handleEvent(const sf::Event&);

	void loadGameControls();

	void bindKeyToAction(const sf::Keyboard::Key&, const std::string&);

	void bindActionToFunction(const std::string&, FunctionPair);
	void bindActionToFunction(const std::string&, voidFunction, voidFunction);

private:

};

#endif