#include "pch.h"
#include "Button.h"

Button::Button(int posX, int posY, int width, int height, bool colisionBoxFRectTText, const sf::Color& buttonColorIdle, const sf::Color& buttonColorHover,
	const char* bname, const sf::Color& textColorIdle, const sf::Color& textColorHover, int charSize, const sf::Font& textFont,
	int borderSize, const sf::Color& borderColor, sf::Sound& hoverSound, sf::Sound& pressedSound)
	:buttonColorIdle(buttonColorIdle), buttonColorHover(buttonColorHover),
	textColorIdle(textColorIdle), textColorHover(textColorHover), hoverSound(hoverSound), pressedSound(pressedSound),
	hover(false)
{
	buttonRect.setPosition(sf::Vector2f(posX, posY));
	buttonRect.setSize(sf::Vector2f(width, height));
	buttonRect.setFillColor(buttonColorIdle);

	if(!colisionBoxFRectTText)
		baseRect = new sf::FloatRect(buttonRect.getGlobalBounds());

	borderRect.setPosition(sf::Vector2f(posX - borderSize, posY - borderSize));
	borderRect.setSize(sf::Vector2f(width + 2 * borderSize, height + 2 * borderSize));
	borderRect.setFillColor(borderColor);

	text.setString(bname);
	text.setCharacterSize(charSize);
	text.setFont(textFont);
	text.setFillColor(textColorIdle);
	text.setStyle(sf::Text::Bold);
	text.setPosition(sf::Vector2f(posX + (width - text.getGlobalBounds().width)/2, posY + (height - text.getGlobalBounds().height) / 2));

	if (colisionBoxFRectTText)
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
			buttonRect.setFillColor(buttonColorHover);
			text.setFillColor(textColorHover);
			hover = true;
			hoverSound.play();
		}	
	}
	else {
		if (hover) {
			buttonRect.setFillColor(buttonColorIdle);
			text.setFillColor(textColorIdle);
			hover = false;
		}
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(borderRect);
	target->draw(buttonRect);
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
