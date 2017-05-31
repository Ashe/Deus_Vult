#ifndef INTERACTIONCOMPONENT_H
#define INTERACTIONCOMPONENT_H

#include <string>
#include "..\Common\Scripts.h" 
#include "Component.h"

class InteractionComponent : public Component {
public:
	InteractionComponent(Entity* e, sol::table& componentTable);
private:

};

#endif // !INTERACTIONCOMPONENT_H
