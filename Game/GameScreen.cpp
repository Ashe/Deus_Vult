#include "GameScreen.h"
#include "../Core/ResourceManagers/ResourceManager.h"

GameScreen::GameScreen(sf::RenderWindow* window)
	:_window(window) {}

void GameScreen::init() {
	_lua.open_libraries();

	lfs::loadFunctions(_lua);

	_controller.initialise(&_input);

	hero("Data/common/spine/hero/export/hero.json", "Data/common/spine/hero/export/hero.skel", "Data/common/spine/hero/export/hero.atlas", 0.8f);
}

bool GameScreen::update(const sf::Time& dTime) {

    EntityList::update(dTime);

	// TEST
		SkeletonBounds_update(_bounds, _skeleton, true);
		_hero->update(dTime.asSeconds());
	// END TEST

	return false;
}

void GameScreen::render(const sf::Time& dTime) {
	sf::Vector2f pos = EntityList::getPlayer()->get<TransformComponent>()->_position;
	_window->setView(sf::View(pos, _window->getView().getSize()));

	EntityList::render(_window, dTime);

	// BEGIN TEST
		_window->draw(*_hero);
	// END TEST
}

void GameScreen::handleEvent(const sf::Event& e) {
	_input.handleEvent(e);
}

void GameScreen::quit() {

	// TEST
		SkeletonBounds_dispose(_bounds);
		SkeletonData_dispose(_skeletonData);

		Atlas_dispose(_atlas);
	//TEST
}

// RANDOM STUFF

void callback(AnimationState* state, EventType type, TrackEntry* entry, Event* event) {
	const char* animationName = (entry && entry->animation) ? entry->animation->name : 0;

	switch (type) {
	case ANIMATION_START:
		printf("%d start: %s\n", entry->trackIndex, animationName);
		break;
	case ANIMATION_INTERRUPT:
		printf("%d interrupt: %s\n", entry->trackIndex, animationName);
		break;
	case ANIMATION_END:
		printf("%d end: %s\n", entry->trackIndex, animationName);
		break;
	case ANIMATION_COMPLETE:
		printf("%d complete: %s\n", entry->trackIndex, animationName);
		break;
	case ANIMATION_DISPOSE:
		printf("%d dispose: %s\n", entry->trackIndex, animationName);
		break;
	case ANIMATION_EVENT:
		printf("%d event: %s, %s: %d, %f, %s\n", entry->trackIndex, animationName, event->data->name, event->intValue, event->floatValue,
			event->stringValue);
		break;
	}
	fflush(stdout);
}

SkeletonData* readSkeletonJsonData(const char* filename, Atlas* atlas, float scale) {
	SkeletonJson* json = SkeletonJson_create(atlas);
	json->scale = scale;
	SkeletonData* skeletonData = SkeletonJson_readSkeletonDataFile(json, filename);
	if (!skeletonData) {
		printf("%s\n", json->error);
		exit(0);
	}
	SkeletonJson_dispose(json);
	return skeletonData;
}

SkeletonData* readSkeletonBinaryData(const char* filename, Atlas* atlas, float scale) {
	SkeletonBinary* binary = SkeletonBinary_create(atlas);
	binary->scale = scale;
	SkeletonData *skeletonData = SkeletonBinary_readSkeletonDataFile(binary, filename);
	if (!skeletonData) {
		printf("%s\n", binary->error);
		exit(0);
	}
	SkeletonBinary_dispose(binary);
	return skeletonData;
}

void GameScreen::hero(const char* jsonName, const char* binaryName, const char* atlasName,
	float scale) {

	// GENERIC FUNC
		_atlas = Atlas_createFromFile(atlasName, 0);
		_skeletonData = readSkeletonJsonData(jsonName, _atlas, scale);
	// END GENERIC FUNC

	_bounds = SkeletonBounds_create();

	// Configure mixing.
	AnimationStateData* stateData = AnimationStateData_create(_skeletonData);
	AnimationStateData_setMixByName(stateData, "Idle", "Walk", 0.2f);
	AnimationStateData_setMixByName(stateData, "Walk", "Crouch", 0.8f);
	AnimationStateData_setMixByName(stateData, "Crouch", "Run", 0.2f);
	AnimationStateData_setMixByName(stateData, "Run", "Attack", 0.5f);
	AnimationStateData_setMixByName(stateData, "Attack", "Run", 0.5f);

	_hero = new spine::SkeletonDrawable(_skeletonData, stateData);
	_hero->timeScale = 1;

	_skeleton = _hero->skeleton;
	_skeleton->flipX = false;
	_skeleton->flipY = false;
	Skeleton_setToSetupPose(_skeleton);

	_skeleton->x = 320;
	_skeleton->y = 460;
	Skeleton_updateWorldTransform(_skeleton);

	_headSlot = Skeleton_findSlot(_skeleton, "head");

	//_hero->state->listener = callback;
	AnimationState_addAnimationByName(_hero->state, 0, "Idle", true, 0);
	AnimationState_addAnimationByName(_hero->state, 0, "Walk", true, 3);
	AnimationState_addAnimationByName(_hero->state, 0, "Crouch", true, 3);
	AnimationState_addAnimationByName(_hero->state, 0, "Run", true, 5);
	AnimationState_addAnimationByName(_hero->state, 0, "Attack", true, 1);
	AnimationState_addAnimationByName(_hero->state, 0, "Run", true, 0.5);

}