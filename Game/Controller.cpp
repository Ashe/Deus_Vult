#include "Controller.h"

#include "../Core/ResourceManagers/ResourceManager.h"

void Controller::initialise(InputManager* input, sol::state& lua) {
	_player = EntityList::getPlayer();

	// Prepare some c++ for later injection
	sol::table cbFuncs = ResourceManager::getTable("combat/system.lua");
	if (cbFuncs["combatButtonPressed"]) _combat = cbFuncs["combatButtonPressed"];

	// Bind keys to actions
	input->bindKeyToAction(sf::Keyboard::A, "moveLeft");
	input->bindKeyToAction(sf::Keyboard::D, "moveRight");
	input->bindKeyToAction(sf::Keyboard::LShift, "sprint");

	input->bindKeyToAction(sf::Keyboard::E, "interact");
	input->bindKeyToAction(sf::Keyboard::Space, "combat");

	// Create std::functions ready for binding
	auto temp = _player->get<ControllerComponent>();
	std::function<void()> moveLeft = std::bind(&ControllerComponent::addDirLeft, temp);
	std::function<void()> moveRight = std::bind(&ControllerComponent::addDirRight, temp);
	std::function<void()> startSprint = std::bind(&ControllerComponent::startSprinting, temp);
	std::function<void()> stopSprint = std::bind(&ControllerComponent::stopSprinting, temp);

	std::function<void()> interact = std::bind(&EntityList::interactWithClosest);
	std::function<void()> combat = std::bind(&Controller::doCombat, *this);

	// Bind actions to functions
	input->bindActionToFunction("moveLeft", moveLeft, moveRight);
	input->bindActionToFunction("moveRight", moveRight, moveLeft);
	input->bindActionToFunction("sprint", startSprint, stopSprint);

	input->bindActionToFunction("interact", interact, NULL);
	input->bindActionToFunction("combat", combat, NULL);
}

void Controller::doCombat() {
	if (_combat) {
		_combat(_player);
	}
}
