#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <functional>
#include <SFML/Graphics.hpp>

#include "../Common/Entity.h"

class InputManager {
public:
	std::map<sf::Keyboard::Key, bool> _keyStatus;

	void handleEvent(const sf::Event&);
	void registerHandle(std::function<void(int, bool)>);

private:
	std::function<void(int, bool)> _handler;
};

#endif