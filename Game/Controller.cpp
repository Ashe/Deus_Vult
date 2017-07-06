#include "Controller.h"

#include "../Core/ResourceManagers/ResourceManager.h"

void Controller::initialise(InputManager* input, HUD* hud) {
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

	if (_movementComponent && _player) {
		_movementComponent->addDirection(-1);
		return;
	}

	// If there's no movementComponent, try again
	_player = EntityList::getPlayer();
	_movementComponent = _player->get<MovementComponent>();
	_movementComponent->addDirection(-1);
}

void Controller::addDirRight() {

	if (_movementComponent && _player) {
		_movementComponent->addDirection(1);
		return;
	}

	// If there's no movementComponent, try again
	_player = EntityList::getPlayer();
	_movementComponent = _player->get<MovementComponent>();
	_movementComponent->addDirection(1);
}

void Controller::startSprinting() {
	if (_movementComponent && _player) {
		_movementComponent->setSprintSpeed(2);
		return;
	}

	// If there's no movementComponent, try again
	_player = EntityList::getPlayer();
	_movementComponent = _player->get<MovementComponent>();
	_movementComponent->setSprintSpeed(2);
}

void Controller::stopSprinting() {
	if (_movementComponent && _player) {
		_movementComponent->setSprintSpeed(1);
		return;
	}

	// If there's no movementComponent, try again
	_player = EntityList::getPlayer();
	_movementComponent = _player->get<MovementComponent>();
	_movementComponent->setSprintSpeed(1);
}

void Controller::doCombat() {
	if (!_player)
		_player = EntityList::getPlayer();

	if (_combat && _player)
		_combat(_player);
}
