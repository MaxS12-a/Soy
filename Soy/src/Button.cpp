#include "pch.h"
#include "Button.h"

// Constructors & destructors
Button::Button(float x, float y, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale, 
	sf::Sound& hoverSound, sf::Sound& pressedSound)
	: GuiItem(x, y, origin, windowResolution, guiScale), hoverSound(hoverSound),pressedSound(pressedSound)
{
}

Button::~Button()
{
}

// Methods
void Button::moveHitBox(float x, float y)
{
	hitBox.left += x;
	hitBox.top += y;
}

bool Button::update(const MouseState& mouseState)
{
	if (hitBox.contains(mouseState.mousePosWindow.x, mouseState.mousePosWindow.y)) {
		if(!hover) hoverSound.play();
		hover = true;
		if (mouseState.mouseClickLeft) {
			pressedSound.play();
			return true;
		}
	}
	else hover = false;

	return false;
}