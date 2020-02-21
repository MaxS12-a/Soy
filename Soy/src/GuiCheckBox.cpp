#include "pch.h"
#include "GuiCheckBox.h"

GuiCheckBox::GuiCheckBox(float x, float y, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale, 
	const std::string& textureFile, const sf::IntRect& baseTextureRect, const sf::Vector2f& scaleOnHover, 
	sf::Sound* hoverSound, sf::Sound* pressedSound)
	: Button(x, y, origin, windowResolution, guiScale, hoverSound, pressedSound),
	scaleOnHover(scaleOnHover), textureRect(baseTextureRect)
{
	texture = new sf::Texture();
	if(!texture->loadFromFile(textureFile)) LOG_CRITICAL("Could not load {0}", textureFile);

	sprite.setTexture(*texture);
	sprite.setTextureRect(textureRect);

	create(windowResolution, guiScale);
}

GuiCheckBox::~GuiCheckBox()
{
	delete texture;
}

bool GuiCheckBox::update(const MouseState& mouseState)
{
	Button::update(mouseState);

	if (hover) {
		if (sprite.getScale().x == guiScale.x && sprite.getScale().y == guiScale.y)
			sprite.setScale(scaleOnHover.x * guiScale.x, scaleOnHover.y * guiScale.y);

		if(mouseState.mouseClickLeft){
			if (marked) {
				textureRect.left = textureRect.width;;
				sprite.setTextureRect(textureRect);
				marked = false;
			} else {	
				textureRect.left = texture->getSize().x - textureRect.width;
				sprite.setTextureRect(textureRect);
				marked = true;
			}
		}else if (!marked && textureRect.left == 0) {
			textureRect.left = textureRect.width;
			sprite.setTextureRect(textureRect);
		}
	}else{
		if (textureRect.left != 0) {
			textureRect.left = 0;
			sprite.setTextureRect(textureRect);
			marked = false;
		}
		if (sprite.getScale().x != guiScale.x && sprite.getScale().y != guiScale.y)
			sprite.setScale(guiScale.x, guiScale.y);
	}

	return false;
}

void GuiCheckBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

void GuiCheckBox::create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale)
{
	this->windowResolution = windowResolution;
	this->guiScale = guiScale;

	setPosition(x / 1920 * windowResolution.x, y / 1080 * windowResolution.y);

	sprite.setOrigin(0, 0);
	std::pair<int, int> newOrigin = getNewOrigin(origin,
		std::pair<int, int>(sprite.getTexture()->getSize().x, sprite.getTexture()->getSize().y));
	sprite.setOrigin(newOrigin.first, newOrigin.second);
	sprite.setScale(guiScale);

	doHitBox();
}

void GuiCheckBox::doHitBox()
{

	hitBox = sprite.getGlobalBounds();
	hitBox.left += getPosition().x;
	hitBox.top += getPosition().y;
}

const sf::FloatRect& GuiCheckBox::getGlobalBounds()
{
	
	return hitBox;
}
