#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <functional>
#include <SFML\Graphics.hpp>

class InputManager {
public:
	struct FunctionPair {
		FunctionPair() {}
		FunctionPair(std::function<void()> kd, std::function<void()> kr)
			: _keyDown(kd), _keyRelease(kr) {}

		std::function<void()> _keyDown = NULL;
		std::function<void()> _keyRelease = NULL;
	};

	std::map<sf::Keyboard::Key, std::string> _keys;
	std::map<sf::Keyboard::Key, bool> _keyStatus;
	std::map<std::string, FunctionPair> _actions;

	void handleEvent(const sf::Event&);

	void bindKeyToAction(const sf::Keyboard::Key&, const std::string&);

	void bindActionToFunction(const std::string&, FunctionPair);
	void bindActionToFunction(const std::string&, std::function<void()>, std::function<void()>);

private:

};

#endif