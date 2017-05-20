#ifndef ANIMWRAPPER_H
#define ANIMWRAPPER_H

#include "AnimatedSprite.hpp"

class AnimWrapper {
public:
	AnimWrapper(const std::string& animationName, const Animation& animation)
		: name(animationName), anim(animation) {}

	const std::string name;
	const Animation anim;
};

#endif // !ANIMWRAPPER_H