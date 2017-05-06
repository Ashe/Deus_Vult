#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <string>
#include "Scripts.h"
#include "Component.h"

class GraphicsComponent : public Component {
public:
	GraphicsComponent(sol::table& componentTable);

	void setFilename(const std::string& filename) {
		this->filename = filename;
	}

	std::string getFilename() const {
		return filename;
	}
private:
	std::string filename;
};

#endif

