#include "pch.h"
#include "Selector.h"

Selector::Selector(int posX, int posY, int charSize, const sf::Font& textFont, sf::Color textColorIdle,	sf::Color textColorHover, 
	const sf::Texture& arrowTextureL, std::vector<sf::VideoMode>* options, sf::Sound& hoverSound, sf::Sound& pressedSound, double guiScale)
	: textColorIdle(textColorIdle), textColorHover(textColorHover), hoverSound(hoverSound), pressedSound(pressedSound)
{
	std::cout << posY << std::endl;
	for (auto i : *options)
		this->options.emplace_back(std::to_string(i.width) + "X" + std::to_string(i.height));

	arrowSpriteL.setTexture(arrowTextureL);
	arrowSpriteL.setScale(guiScale, guiScale);
	arrowSpriteR.setTexture(arrowTextureL);
	arrowSpriteR.setRotation(180);
	
	text.setPosition(sf::Vector2f(posX + arrowSpriteL.getGlobalBounds().width, posY ));

	text.setString(this->options[0]);
	text.setCharacterSize(charSize);
	text.setFont(textFont);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(textColorIdle);

	arrowSpriteL.setPosition(text.getPosition().x - arrowSpriteL.getGlobalBounds().width, 
		text.getGlobalBounds().top + text.getGlobalBounds().height/2 - arrowSpriteL.getGlobalBounds().height/2);
	arrowSpriteR.setPosition(text.getPosition().x + text.getGlobalBounds().width + arrowSpriteR.getGlobalBounds().width,
		text.getGlobalBounds().top + text.getGlobalBounds().height/2 + arrowSpriteR.getGlobalBounds().height/2);
	
	textRect = sf::FloatRect(text.getGlobalBounds());
	arrowRectL = sf::FloatRect(arrowSpriteL.getGlobalBounds());
	arrowRectR = sf::FloatRect(arrowSpriteR.getGlobalBounds());
}

Selector::~Selector()
{

}

void Selector::update(sf::Vector2i mousePosWindow)
{
	/*if(textRect.contains(mousePosWindow.x, mousePosWindow.y) 
		|| arrowRectL.contains(mousePosWindow.x, mousePosWindow.y) 
		|| arrowRectR.contains(mousePosWindow.x, mousePosWindow.y)){
		if (!hover) {
			text.setFillColor(textColorHover);
			hover = true;
			hoverSound.play();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

		}
	} else if (hover) {
		text.setFillColor(textColorIdle);
		hover = false;
	}
	



	textRect = sf::FloatRect(text.getGlobalBounds());
	arrowRectL = sf::FloatRect(arrowSpriteL.getGlobalBounds());
	arrowRectR = sf::FloatRect(arrowSpriteR.getGlobalBounds());

	arrowSpriteL.setPosition(text.getPosition().x - arrowSpriteL.getGlobalBounds().width - 10,
		text.getPosition().y + text.getGlobalBounds().height / 2 - arrowSpriteL.getGlobalBounds().height / 2);
	arrowSpriteR.setPosition(text.getPosition().x + text.getGlobalBounds().width + arrowSpriteR.getGlobalBounds().width + 10,
		text.getPosition().y + text.getGlobalBounds().height / 2 - arrowSpriteR.getGlobalBounds().height / 2);*/
}

void Selector::render(sf::RenderTarget* target)
{
	target->draw(arrowSpriteL);
	target->draw(text);
	target->draw(arrowSpriteR);
}

