#include "pch.h"
#include "Button.h"

Button::Button(int posX, int posY, const char* bname, 
	const sf::Color& textColorIdle, const sf::Color& textColorHover, int charSize, const sf::Font& textFont,
	sf::Sound& hoverSound, sf::Sound& pressedSound)
	:textColorIdle(textColorIdle), textColorHover(textColorHover), hoverSound(hoverSound), pressedSound(pressedSound),
	hover(false)
{
	text.setString(bname);
	text.setCharacterSize(charSize);
	text.setFont(textFont);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(textColorIdle);
	text.setPosition(sf::Vector2f(posX - text.getGlobalBounds().width/2, posY  - text.getGlobalBounds().height / 2));
	baseRect = new sf::FloatRect(text.getGlobalBounds());
}

Button::~Button()
{
	delete baseRect;
}

void Button::update(sf::Vector2i mousePosWindow)
{
	if (baseRect->contains(mousePosWindow.x , mousePosWindow.y)) {
		if (!hover) {
			text.setFillColor(textColorHover);
			hover = true;
			hoverSound.play();
		}	
	}
	else {
		if (hover) {
			text.setFillColor(textColorIdle);
			hover = false;
		}
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(text);
}

void Button::press()
{
	pressedSound.play();
}

const bool Button::getHover() const
{
	return hover;
}

const sf::FloatRect Button::getGlobalBounds() const {
	return text.getGlobalBounds();
}