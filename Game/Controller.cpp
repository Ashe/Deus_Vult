#include "Controller.h"

#include "../Core/ResourceManagers/ResourceManager.h"

void Controller::initialise(InputManager* input, HUD* hud) {
	_player = EntityList::getPlayer();
	_hud = hud;

	// Prepare some c++ for later injection

	printf("-----------------------------\nLoading Input System...\n-----------------------------\n");

	sol::table inputT = ResourceManager::getTable("systems/main.lua");
	if (inputT["handleInput"]) {
		printf("|- Attempting to register input handler...\n");
		_handleInput = inputT["handleInput"];
		input->registerHandle([this](int i, bool b) { this->handleInput(i, b); });
		printf("|- Loading successful.\n");
	}
	else printf("|- Error: No input handler found.\n");

	printf("-----------------------------\n Main Input Loaded.\n-----------------------------\n");


	printf("-----------------------------\nLoading Combat System...\n-----------------------------\n");

	sol::table cbFuncs = ResourceManager::getTable("systems/combatSystem.lua");
	//if (cbFuncs["combatFunc"]) _combat = cbFuncs["combatFunc"];
	if (cbFuncs["validStats"]) _validStats = cbFuncs["validStats"];

	if (_hud) _hud->loadStatsToShow(_validStats);
	printf("-----------------------------\n Combat System Loaded.\n-----------------------------\n");
}

void Controller::handleInput(int i, bool b) {
	if (!_player)
		_player = EntityList::getPlayer();

	_handleInput(_player, i, b);
}