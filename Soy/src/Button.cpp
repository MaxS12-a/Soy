#include "pch.h"
#include "Button.h"

Button::Button(float x, float y,  const sf::Vector2f& guiScale, const sf::Vector2f& origin,
	const sf::Vector2u& windowResolution, sf::Sound& hoverSound, sf::Sound& pressedSound)
	: GuiItem(x, y, guiScale, origin, windowResolution), hoverSound(hoverSound),pressedSound(pressedSound)
{
}

Button::~Button()
{
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