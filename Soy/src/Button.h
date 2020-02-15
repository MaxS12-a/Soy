#pragma once
#include "GuiItem.h"

class Button :
	public GuiItem
{
public:
	Button(float x, float y, const sf::Vector2f& guiScale, const sf::Vector2f& origin, const sf::Vector2u& windowResolution,
		sf::Sound& hoverSound, sf::Sound& pressedSound);
	virtual ~Button();

	virtual bool update(const MouseState& mouseState);
protected:
	sf::FloatRect hitBox;

	bool hover;

	sf::Sound& hoverSound;
	sf::Sound& pressedSound;
};

