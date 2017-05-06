#include "GraphicsComponent.h"
#include <sol.hpp>
#include <iostream>

GraphicsComponent::GraphicsComponent(sol::table& componentTable) {
	auto filenameRef = componentTable["filename"];
	if (true){//filenameRef.isString()) {
		filename = filenameRef;
	}
	else {
		std::cout << "Error, GraphicsComponent.filename is not a string!" << std::endl;
	}
}