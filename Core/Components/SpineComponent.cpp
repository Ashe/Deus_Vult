#include "SpineComponent.h"
#include "../Common/Scripts.h"

#include "../Common/Entity.h"

#include "../ResourceManagers/ResourceManager.h"

SpineComponent::SpineComponent(Entity* e, sol::table& componentTable) : GraphicsComponentBase(e) {
	_transform = _owner->get<TransformComponent>();

	// Get the outline component if it exists
	_noOutline = false;
	_outline = _owner->get<OutlineComponent>();
	if (_outline)
		_outlineThickness = _outline->_thickness;

	// Query the data format
	_dataIsJSON = false;
	if (componentTable["dataIsJSON"])
		_dataIsJSON = componentTable["dataIsJSON"];

	// Get the atlas
	auto atlasNameRef = componentTable["atlas"];
	if (atlasNameRef.valid()) {
		_atlasFile = atlasNameRef;
		_atlasFile = "Data/" + _atlasFile;
		_atlas = Atlas_createFromFile(_atlasFile.c_str(), 0);
		if (!_atlas) {
			printf("Error: No atlas found for path %s.", _atlasFile.c_str());
			return;
		}
	}
	else
		printf("Error: atlas path invalid.");

	_scale = 1;
	if (componentTable["scale"])
		_scale = componentTable["scale"];

	// Get the JSON/Binary
	auto dataNameRef = componentTable["data"];
	if (dataNameRef.valid()) {
		_dataFile = dataNameRef;
		_dataFile = "Data/" + _dataFile;

		if (!_dataIsJSON)
			_skeletonData = readSkeletonBinaryData(_dataFile.c_str(), _atlas, _scale);
		else
			_skeletonData = readSkeletonJsonData(_dataFile.c_str(), _atlas, _scale);

		_bounds = SkeletonBounds_create();

		// Configure mixing.
		AnimationStateData* stateData = AnimationStateData_create(_skeletonData);
		//AnimationStateData_setMixByName(stateData, "Idle", "Walk", 0.2f);
		//AnimationStateData_setMixByName(stateData, "Walk", "Crouch", 0.8f);
		//AnimationStateData_setMixByName(stateData, "Crouch", "Run", 0.2f);
		//AnimationStateData_setMixByName(stateData, "Run", "Attack", 0.5f);
		//AnimationStateData_setMixByName(stateData, "Attack", "Run", 0.5f);

		_spine = new spine::SkeletonDrawable(_skeletonData, stateData);

		_skeleton = _spine->skeleton;
		if (_transform) {
			_skeleton->flipX = _transform->_flipX;
			_skeleton->flipY = _transform->_flipY;
			Skeleton_setToSetupPose(_skeleton);

			_skeleton->x = _transform->_position.x;
			_skeleton->y = _transform->_position.y;
			Skeleton_updateWorldTransform(_skeleton);
		}
		else {
			_skeleton->flipX = false;
			_skeleton->flipY = false;
			Skeleton_setToSetupPose(_skeleton);

			_skeleton->x = 0;
			_skeleton->y = 0;
			Skeleton_updateWorldTransform(_skeleton);
		}

		if (_debug)
			_spine->state->listener = callback;

		//AnimationState_addAnimationByName(_spine->state, 0, "Idle", true, 0);
		//AnimationState_addAnimationByName(_spine->state, 0, "Walk", true, 3);
		//AnimationState_addAnimationByName(_spine->state, 0, "Crouch", true, 3);
		//AnimationState_addAnimationByName(_spine->state, 0, "Run", true, 5);
		//AnimationState_addAnimationByName(_spine->state, 0, "Attack", true, 1);
		//AnimationState_addAnimationByName(_spine->state, 0, "Run", true, 0.5);

		//// Set sizes
		_spriteWidth = _spine->vertexArray->getBounds().width;
		_spriteHeight = _spine->vertexArray->getBounds().height;

		//// Set sprite colour
		//_spriteColour = sf::Color::White;
		//if (componentTable["spriteColour"]) {
		//	int valid = 0;
		//	for (int i = 1; i < 5; i++) {
		//		if (componentTable["spriteColour"][i])
		//			valid += 1;
		//	}
		//	if (valid == 4)
		//		_spriteColour = sf::Color(componentTable["spriteColour"][1], componentTable["spriteColour"][2], componentTable["spriteColour"][3], componentTable["spriteColour"][4]);
		//}

		_timeScale = 1;
		if (componentTable["timeScale"])
			_timeScale = componentTable["timeScale"];

		_spine->timeScale = 1;

		_defaultMix = 0;
		if (componentTable["defaultMix"])
			_defaultMix = componentTable["defaultMix"];

		_spine->state->data->defaultMix = 0.2;

		auto skinRef = componentTable["skin"];
		if (skinRef.valid()) {
			std:: string skin = skinRef;
			spSkeleton_setSkin(_skeleton, spSkeletonData_findSkin(_skeletonData, skin.c_str()));
		}


		// If there's any animations, set them. Else, take the entire file as the only sprite
		sol::table animations = componentTable["animations"];
		if (animations) {
			setAnimations(animations);

			auto animRef = componentTable["defaultAnim"];
			if (animRef.valid())
				changeAnimation(animRef);
			else {
				if (_animationList.count("idle")) {
					changeAnimation(_animationList["idle"]);
					printf("No valid default animation, using %s.\n", _animationList["idle"].c_str());
				}
				else {
					changeAnimation(_animationList.begin()->first);
					printf("No valid default animation, using %s.\n", _animationList.begin()->first.c_str());
				}
			}
		}

	}
	else {
		printf("Error, GraphicsComponent.filename is not a string!\n");
	}


	// Add the render function to the list of functions to render
	_owner->addRenderFunction([this](sf::RenderWindow* window, const sf::Time&dTime) {render(window, dTime); });
}

SpineComponent::~SpineComponent() {

	delete _spine;
	SkeletonBounds_dispose(_bounds);
	SkeletonData_dispose(_skeletonData);

	Atlas_dispose(_atlas);
}

void SpineComponent::render(sf::RenderWindow* window, const sf::Time& dTime) {
	if (_transform) {

		SkeletonBounds_update(_bounds, _skeleton, true);
		_spine->update(dTime.asSeconds());

		_spine->skeleton->root->scaleX = _transform->_scale.x;
		_spine->skeleton->root->scaleY = _transform->_scale.y;

		_spine->skeleton->flipX = _transform->_flipX;
		_spine->skeleton->flipY = _transform->_flipY;

		_spine->skeleton->x = _transform->_position.x;
		_spine->skeleton->y = _transform->_position.y;

		//if (_outline && _outlineThickness > 0)
		//	drawOutline(window);
		//else if (!_noOutline) {
		//	// If there's no outline module, find it
		//	// BUT flip the bool so no further attempts are made
		//	_noOutline = true;
		//	_outline = _owner->get<OutlineComponent>();
		//	if (_outline)
		//		_outlineThickness = _outline->_thickness;
		//}

		spColor_setFromFloats(&_spriteColour, 1.f, 1.f, 1.f, 1.f);
		_spine->skeleton->color = _spriteColour;

		window->draw(*_spine);

		//// DEV MODE
		//sf::RectangleShape rect;
		//rect.setSize(sf::Vector2f(_spine->vertexArray->getBounds().width, _spine->vertexArray->getBounds().height));
		//sf::Vector2f pos(_spine->skeleton->x, _spine->skeleton->y);
		//sf::Vector2f center(_spine->vertexArray->getBounds().width / 2, _spine->vertexArray->getBounds().height);
		//rect.setPosition(pos - center);
		//rect.setFillColor(sf::Color::Transparent);
		//rect.setOutlineColor(sf::Color::White);
		//rect.setOutlineThickness(2);
		//window->draw(rect);

		return;
	}

	// if there's no transform component, try again
	_transform = _owner->get<TransformComponent>();
}

void SpineComponent::changeAnimation(const std::string& animName) {

	// Clear the animation queue and change the animation
	if (animName != _currentAnimation) {
		if (_animationList.count(animName)) {
			_currentAnimation = animName;
			AnimationState_setAnimationByName(_spine->state, 0, _animationList[animName].c_str(), true);
			//printf("%s: Animation changed to: %s.\n", _owner->getType().c_str(), animName.c_str());
			return;
		}

		printf("No animations with %s found.\n", animName.c_str());
	}
}

void SpineComponent::playAnimation(const std::string& animName, float delay) {

	// This function plays an animation and queue's the current animation to play after the delay
	if (animName != _currentAnimation) {
		if (_animationList.count(animName)) {
			AnimationState_setAnimationByName(_spine->state, 0, _animationList[animName].c_str(), true);
			AnimationState_addAnimationByName(_spine->state, 0, _animationList[_currentAnimation].c_str(), true, delay);
			//printf("%s: Animation changed to: %s.\n", _owner->getType().c_str(), animName.c_str());
			return;
		}
		printf("No animations with %s found.\n", animName.c_str());
	}
}

sf::Vector2i SpineComponent::getSize() const {
	return sf::Vector2i(_spine->vertexArray->getBounds().width, _spine->vertexArray->getBounds().height);
}

void SpineComponent::setAnimations(sol::table & animationTable) {
	for (auto key_value_pair : animationTable) {
		// Get the name and table for every formal animation
		std::string animationName = key_value_pair.first.as<std::string>();
		sol::object& value = key_value_pair.second;
		sol::table detailsTable = value.as<sol::table>();

		// If the string name is valid, place it into the map
		auto ref = detailsTable["animString"];
		if (ref.valid()) {
			_animationList[animationName] = detailsTable["animString"];
		}

	}
}

//void SpineComponent::drawOutline(sf::RenderWindow* window) {
//	_animatedSprite.setColor(_outline->getOutlineColour());
//
//	_animatedSprite.setPosition(_transform->_position.x + _outlineThickness, _transform->_position.y);
//	window->draw(_animatedSprite);
//
//	_animatedSprite.setPosition(_transform->_position.x - _outlineThickness, _transform->_position.y);
//	window->draw(_animatedSprite);
//
//	_animatedSprite.setPosition(_transform->_position.x, _transform->_position.y + _outlineThickness);
//	window->draw(_animatedSprite);
//
//	_animatedSprite.setPosition(_transform->_position.x, _transform->_position.y - _outlineThickness);
//	window->draw(_animatedSprite);
//}

SkeletonData* SpineComponent::readSkeletonJsonData(const char* filename, Atlas* atlas, float scale) {
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

SkeletonData* SpineComponent::readSkeletonBinaryData(const char* filename, Atlas* atlas, float scale) {
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

void SpineComponent::callback(AnimationState* state, EventType type, TrackEntry* entry, Event* event) {
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
