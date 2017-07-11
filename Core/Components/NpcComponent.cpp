#include "NpcComponent.h"
#include "../Common/Scripts.h"

#include "../Common/Entity.h"

NpcComponent::NpcComponent(Entity* e, sol::table& NpcTable) : Component(e) {

	_showMessage = false;
	_textAdjustReady = false;
	auto phraseRef = NpcTable["initialMessage"];
    if (phraseRef) {
        if (phraseRef.valid()) {
            std::string phrase = phraseRef;
            phrase.c_str();
            setTextString(phrase);
            _showMessage = true;
        }
        else {
            printf("Error, NpcComponent.initialmessage is not a string!\n");
        }
    }

	_speechEnabled = false;
	if (NpcTable["enableSpeech"]) {
		enableSpeech();
	}

	_facePlayer = false;
	if (NpcTable["facePlayer"]) {
		_facePlayer = NpcTable["facePlayer"];
	}

	_sensoryComponent = _owner->get<SensoryComponent>();
	_transform = _owner->get<TransformComponent>();

	// Add update function to functionlist
	_owner->addUpdateFunction([this](const sf::Time&dTime) {update(dTime);});
}

void NpcComponent::printText() {
	std::string phrase = _text.getString();
	printf("%s\n", phrase.c_str());
}

void NpcComponent::setTextString(const std::string& text) {
	_text.setString(text);
	centerText();
}

void NpcComponent::setShowText(bool show) {
	_showMessage = show;

	if (!_speechEnabled)
		enableSpeech();
}

void NpcComponent::update(const sf::Time& dTime) {
	if (_transform && _sensoryComponent) {
		if (_facePlayer) {
			float playerX = _sensoryComponent->getPlayerPos().x;
				_transform->_flipX = playerX < _transform->_position.x;
		}
		return;
	}

	_sensoryComponent = _owner->get<SensoryComponent>();
	_transform = _owner->get<TransformComponent>();
	_spriteDimY = _owner->getSize().y;
}

void NpcComponent::render(sf::RenderWindow* window, const sf::Time& dTime) {

	if (_showMessage && _transform && _textAdjustReady) {

		_spriteDimY = _owner->getSize().y;

		_text.setPosition(_transform->_position);
		_text.move(_textAdjust.x, _textAdjust.y - _spriteDimY);
		window->draw(_text);
		return;
	}

	_transform = _owner->get<TransformComponent>();


	centerText();
}

void NpcComponent::enableSpeech() {
	if (!_speechEnabled) {
		_speechEnabled = true;

		_text.setFont(*ResourceManager::getFont("common/fonts/belgrano/regular.ttf"));
		_text.setOrigin(_text.getCharacterSize() / 3, _text.getCharacterSize() / 2);

		// Add render function to functionlist
		_owner->addRenderFunction([this](sf::RenderWindow* window, const sf::Time& dTime) {render(window, dTime); });
	}
}

void NpcComponent::setFacePlayer(bool face) {
	_facePlayer = face;
}

void NpcComponent::centerText() {
	if (_transform) {

		//center text
		sf::FloatRect textRect = _text.getLocalBounds();
		_textAdjust = sf::Vector2f(textRect.left - textRect.width / 2.0f,
			textRect.top - textRect.height / 2.0f);
	}

	_textAdjustReady = _textAdjust.x != 0 && _textAdjust.y != 0;
}
