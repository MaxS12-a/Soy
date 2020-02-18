#pragma once
#include "GuiItem.h"

// Abstract class for all the buttons
class Button :
	public GuiItem
{
public:
	// Constructors & destructors
	Button(float x, float y, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale, 
		sf::Sound& hoverSound, sf::Sound& pressedSound);
	virtual ~Button();

	// Methods
	virtual void doHitBox() = 0;
	virtual void moveHitBox(float x, float y);

	// update the hover field, play the sounds and return true if pressed
	virtual bool update(const MouseState& mouseState);

protected:
	sf::FloatRect hitBox;

	bool hover;

	sf::Sound& hoverSound;
	sf::Sound& pressedSound;
};

