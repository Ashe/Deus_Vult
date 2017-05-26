#include "InputManager.h"

void InputManager::handleEvent(const sf::Event& e) {
	// If there's a mapping for both key and action
	if (_keys.count(e.key.code) && _actions.count(_keys[e.key.code])) {

		if (e.type == sf::Event::KeyPressed) {

			// If the key is pressed but there's no record / it is not held, call+register
			if (!_keyStatus.count(e.key.code) || !_keyStatus[e.key.code]) {
				// printf("Pressed key for %s!\n", _keys[e.key.code].c_str());
				_keyStatus[e.key.code] = true;

				if (_actions[_keys[e.key.code]]._keyDown != NULL)
					_actions[_keys[e.key.code]]._keyDown();
			}
		}
		else if (e.type == sf::Event::KeyReleased) {
			// printf("Released key for %s!\n", _keys[e.key.code].c_str());
			_keyStatus[e.key.code] = false;

			if (_actions[_keys[e.key.code]]._keyRelease != NULL)
				_actions[_keys[e.key.code]]._keyRelease();
		}
	}
}

void InputManager::bindKeyToAction(const sf::Keyboard::Key& key, const std::string& action) {
	_keys[key] = action;
}

void InputManager::bindActionToFunction(const std::string& action, FunctionPair pair) {
	_actions[action] = pair;
}

void InputManager::bindActionToFunction(const std::string& action, std::function<void()> a, std::function<void()> b) {
	_actions[action] = FunctionPair(a, b);
}
