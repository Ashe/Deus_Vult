#include "InputManager.h"

void InputManager::handleEvent(const sf::Event& e) {

	// If there's a mapping for both key and action
	if (e.type == sf::Event::KeyPressed) {
		if (_handler && (!_keyStatus.count(e.key.code) || !_keyStatus[e.key.code])) {
			_handler(e.key.code, true);
			_keyStatus[e.key.code] = true;
		}
	}
	else if (e.type == sf::Event::KeyReleased) {
		if (_handler) {
			_keyStatus[e.key.code] = false;
			_handler(e.key.code, false);
		}
	}
}

void InputManager::registerHandle(std::function<void(int, bool)> handle) {
	_handler = handle;
}