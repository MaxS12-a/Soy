#include "pch.h"
#include "GuiSprite.h"

GuiSprite::GuiSprite(float x, float y, const std::string& textureFile, const sf::Vector2f& guiScale, 
	const sf::Vector2f& origin, const sf::Vector2u& windowResolution)
	: GuiItem(x, y, guiScale, origin, windowResolution) 
{
	texture = new sf::Texture();
	if (!texture->loadFromFile(textureFile)) LOG_CRITICAL("Could not load {0}", textureFile);

	sprite.setTexture(*texture);

	create(windowResolution, guiScale);
}

GuiSprite::~GuiSprite()
{
	delete texture;
}

void GuiSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

const sf::FloatRect& GuiSprite::getGlobalBounds()
{
	return sf::FloatRect(getPosition(), {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height});
}

void GuiSprite::create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale)
{
	this->guiScale = guiScale;

	setPosition(x / 1920 * windowResolution.x, y / 1080 * windowResolution.y);

	sprite.setOrigin(0, 0);
	std::pair<int, int> newOrigin = getNewOrigin(origin,
		std::pair<int, int>(sprite.getTexture()->getSize().x, sprite.getTexture()->getSize().y));
	sprite.setOrigin(newOrigin.first, newOrigin.second);
	sprite.setScale(guiScale);
}
