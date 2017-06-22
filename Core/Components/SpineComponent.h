#ifndef SPINECOMPONENT_H
#define SPINECOMPONENT_H

#include "GraphicsComponentBase.h"

#include "OutlineComponent.h"
#include "TransformComponent.h"
#include <spine/spine-sfml.h>


class SpineComponent : public GraphicsComponentBase {
public:
	SpineComponent(Entity* e, sol::table& componentTable);
	~SpineComponent();

	void render(sf::RenderWindow*, const sf::Time&);

	void changeAnimation(const std::string&);
	void playAnimation(const std::string&, float);

	sf::Vector2i getSize() const;

private:
	std::string _currentAnimation;

	// Sprite details
	int _spriteWidth = 32;
	int _spriteHeight = 32;
	float _timeScale;
	float _defaultMix;
	spColor _spriteColour;

	// Spine details
	std::string _dataFile;
	std::string _atlasFile;
	float _scale;
	bool _dataIsJSON;

	// Spine Information
	spine::SkeletonDrawable* _spine;
	SkeletonBounds* _bounds;
	SkeletonData* _skeletonData;
	Atlas* _atlas;
	Skeleton* _skeleton;
	bool _debug;

	// Animations
	std::map<std::string, std::string> _animationList;

	// Component links
	TransformComponent* _transform;
	OutlineComponent* _outline;
	float _outlineThickness;
	bool _noOutline;

	void setAnimations(sol::table&);
	void drawOutline(sf::RenderWindow*);

	SkeletonData* readSkeletonJsonData(const char* filename, Atlas* atlas, float scale);
	SkeletonData* readSkeletonBinaryData(const char* filename, Atlas* atlas, float scale);
	static void callback(AnimationState* state, EventType type, TrackEntry* entry, Event* event);
};

#endif