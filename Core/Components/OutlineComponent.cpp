#include "OutlineComponent.h"

#include "..\ResourceManagers\EntityList.h"

OutlineComponent::OutlineComponent(Entity * e, sol::table & componentTable) : Component(e) {
	// Set outline thickness
	if (componentTable["thickness"])
		_thickness = componentTable["thickness"];
	else
		_thickness = 5;

	// Set distances
	if (componentTable["distanceWeak"])
		_distanceWeak = componentTable["distanceWeak"];
	else
		_distanceWeak = 0;

	// Set distances
	if (componentTable["distanceStrong"])
		_distanceStrong = componentTable["distanceStrong"];
	else
		_distanceStrong = 0;

	// Set closest outline colour
	_colour = sf::Color::Black;
	if (componentTable["colour"]) {
		int valid = 0;
		for (int i = 1; i < 5; i++) {
			if (componentTable["colour"][i])
				valid += 1;
		}
		if (valid == 4)
			_colour = sf::Color(componentTable["colour"][1], componentTable["colour"][2], componentTable["colour"][3], componentTable["colour"][4]);
	}

	_thisPosition = _owner->get<TransformComponent>();
}

sf::Color OutlineComponent::getOutlineColour() {

	if (_playerPosition && _thisPosition) {
		// If there's a player position, base the outline on it
		float distance = abs(_playerPosition->_position.x - _thisPosition->_position.x);
		if (distance < _distanceWeak) {

			// Easy out for if the distance needs no interpolating
			if (distance < _distanceStrong)
				return _colour;

			// If you're somewhere inbetween, interpolate
			float alpha = (1 - ((distance - _distanceStrong) / (_distanceWeak - _distanceStrong))) * _colour.a;
			
			return sf::Color(_colour.r, _colour.g, _colour.b, alpha);
		}
		else
			return sf::Color::Transparent;
	}

	if (_distanceWeak <= 0) {
		// If there's no distance requirement, display the full str colour
		return _colour;
	}

	// If no player to base outline off nor any other info, return transparent
	_playerPosition = EntityList::getPlayer()->get<TransformComponent>();
	_thisPosition = _owner->get<TransformComponent>();
	return sf::Color::Transparent;
}
