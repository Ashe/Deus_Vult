#include "Controller.h"

#include "../Core/ResourceManagers/ResourceManager.h"

void Controller::initialise(InputManager* input, HUD* hud, sol::state& lua) {
	_player = EntityList::getPlayer();
	_hud = hud;

	// Prepare some c++ for later injection
	printf("-----------------------------\nLoading Combat System...\n-----------------------------\n");

	sol::table cbFuncs = ResourceManager::getTable("combat/system.lua");
	if (cbFuncs["combatFunc"]) _combat = cbFuncs["combatFunc"];
	if (cbFuncs["validStats"]) _validStats = cbFuncs["validStats"];

	if (_hud) _hud->loadStatsToShow(_validStats);
	printf("-----------------------------\n Combat System Loaded.\n-----------------------------\n");

	// Bind keys to actions
	input->bindKeyToAction(sf::Keyboard::A, "moveLeft");
	input->bindKeyToAction(sf::Keyboard::D, "moveRight");
	input->bindKeyToAction(sf::Keyboard::LShift, "sprint");

	input->bindKeyToAction(sf::Keyboard::E, "interact");
	input->bindKeyToAction(sf::Keyboard::Space, "combat");

	// Create std::functions ready for binding
	std::function<void()> moveLeft = std::bind(&Controller::addDirLeft, *this);
	std::function<void()> moveRight = std::bind(&Controller::addDirRight, *this);
	std::function<void()> startSprint = std::bind(&Controller::startSprinting, *this);
	std::function<void()> stopSprint = std::bind(&Controller::stopSprinting, *this);

	std::function<void()> interact = std::bind(&EntityList::interactWithClosest);
	std::function<void()> combat = std::bind(&Controller::doCombat, *this);

	// Bind actions to functions
	input->bindActionToFunction("moveLeft", moveLeft, moveRight);
	input->bindActionToFunction("moveRight", moveRight, moveLeft);
	input->bindActionToFunction("sprint", startSprint, stopSprint);

	input->bindActionToFunction("interact", interact, NULL);
	input->bindActionToFunction("combat", combat, NULL);
}

void Controller::addDirLeft() {

	if (_movementComponent) {
		_movementComponent->addDirection(-1);
		//printf("\tMove Left,  direction: %d\n", _movementComponent->_direction);
		return;
	}

	// If there's no movementComponent, try again
	_movementComponent = _player->get<MovementComponent>();
	_movementComponent->addDirection(-1);

	//printf("No MovementComponent found on moveLeft. Trying again..\n");
	//addDirLeft();
}

void Controller::addDirRight() {

	if (_movementComponent) {
		_movementComponent->addDirection(1);

		//printf("\tMove Right, direction: %d\n", _movementComponent->_direction);
		return;
	}

	// If there's no movementComponent, try again
	_movementComponent = _player->get<MovementComponent>();
	_movementComponent->addDirection(1);
	//printf("No MovementComponent found on moveRight. Trying again..\n");
	//addDirRight();
}

void Controller::startSprinting() {
	if (_movementComponent) {
		_movementComponent->setSprintSpeed(2);
		//printf("\tStart Sprint, multiplier: %d\n", _movementComponent->_speedMultiplier);
		return;
	}

	// If there's no movementComponent, try again
	_movementComponent = _player->get<MovementComponent>();
	_movementComponent->setSprintSpeed(2);
	//printf("No MovementComponent found on startSprinting. Trying again..\n");
}

void Controller::stopSprinting() {
	if (_movementComponent) {
		_movementComponent->setSprintSpeed(1);
		//printf("\tStop Sprint, multiplier: %d\n", _movementComponent->_speedMultiplier);
		return;
	}

	// If there's no movementComponent, try again
	_movementComponent = _player->get<MovementComponent>();
	_movementComponent->setSprintSpeed(1);
	//printf("No MovementComponent found on stopSprinting. Trying again..\n");
}

void Controller::doCombat() {
	if (_combat) {
		_combat(_player);
	}
}
