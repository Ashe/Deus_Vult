#include "GraphicsComponent.h"
#include <sol.hpp>

GraphicsComponent::GraphicsComponent(sol::table& componentTable) {
	auto filenameRef = componentTable["filename"];
	if (filenameRef.valid()) {
		filename = filenameRef;
	}
	else {
		printf("Error, GraphicsComponent.filename is not a string!\n");
	}
}