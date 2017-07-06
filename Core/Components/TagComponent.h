#ifndef TAGCOMPONENT_H
#define TAGCOMPONENT_H

#include <string>
#include "../Common/Scripts.h"
#include "Component.h"

class TagComponent : public Component {
public:
	TagComponent(Entity* e, sol::table& componentTable);

private:
	std::vector<std::string> _tags;
};

#endif // !SENSORYCOMPONENT_H
