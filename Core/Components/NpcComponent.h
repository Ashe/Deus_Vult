#ifndef NPCCOMPONENT_H
#define NPCCOMPONENT_H

#include <string>
#include "../Common/Scripts.h" 
#include "Component.h"

#include <SFML/Graphics.hpp>
#include "SensoryComponent.h"
#include "TransformComponent.h"

class NpcComponent : public Component {
public:
	NpcComponent(Entity* e, sol::table& componentTable);
	
	void update(const sf::Time&);
	void render(sf::RenderWindow*, const sf::Time&);

	void printText();
	void setTextString(const std::string&);
	void setShowText(bool);

	void setFacePlayer(bool);

private:
	void enableSpeech();
	void centerText();

	bool _speechEnabled;
	bool _showMessage;
	bool _textAdjustReady;
	sf::Vector2f _textAdjust;
	sf::Text _text;

	bool _facePlayer;

	SensoryComponent* _sensoryComponent;
	TransformComponent* _transform;

	int _spriteDimY;
};

#endif 