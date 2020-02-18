#include "pch.h"
#include "GuiSprite.h"

// Constructos & destructors
GuiSprite::GuiSprite(float x, float y, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale,
	const std::string& textureFile)
	: GuiItem(x, y, origin, windowResolution, guiScale)
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

// GL methods
void GuiSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

void GuiSprite::create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale)
{
	this->guiScale = guiScale;

	setPosition(x / 1920 * windowResolution.x, y / 1080 * windowResolution.y);

	sprite.setOrigin(0, 0);
	std::pair<int, int> newOrigin = getNewOrigin(origin,
		std::pair<int, int>(sprite.getTexture()->getSize().x, sprite.getTexture()->getSize().y));
	sprite.setOrigin(newOrigin.first, newOrigin.second);
	sprite.setScale(guiScale.x * windowResolution.x / 1920 , guiScale.y * windowResolution.y / 1080);
}

// Specific methods
const sf::FloatRect& GuiSprite::getGlobalBounds()
{
	return sf::FloatRect(getPosition(), { sprite.getGlobalBounds().width, sprite.getGlobalBounds().height });
}