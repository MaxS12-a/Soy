#include "pch.h"
#include "SpriteButton.h"

// Constructors & destructors
SpriteButton::SpriteButton(float x, float y, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale, 
	const std::string& textureFile, const sf::Vector2f& scaleOnHover, sf::Sound& hoverSound, sf::Sound& pressedSound)
	: Button(x, y, origin, windowResolution, guiScale, hoverSound, pressedSound),
	scaleOnHover(scaleOnHover)
{
	idleTexture = new sf::Texture();
	if (!idleTexture->loadFromFile(textureFile)) LOG_CRITICAL("Could not load {0}", textureFile);

	sprite.setTexture(*idleTexture);

	create(windowResolution, guiScale);
}

SpriteButton::~SpriteButton()
{
	delete idleTexture;
}

// GL methods
bool SpriteButton::update(const MouseState& mouseState)
{
	if (Button::update(mouseState))
		return true;

	if(hover) {
		if (sprite.getScale().x == guiScale.x && sprite.getScale().y == guiScale.y)
			sprite.setScale(scaleOnHover.x * guiScale.x, scaleOnHover.y * guiScale.y);
	}
	else if (sprite.getScale().x != guiScale.x || sprite.getScale().y != guiScale.y)
		sprite.setScale(guiScale);

	return false;
}

void SpriteButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

void SpriteButton::create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale)
{
	this->guiScale = guiScale;

	setPosition(x / 1920 * windowResolution.x, y / 1080 * windowResolution.y);

	sprite.setOrigin(0, 0);
	std::pair<int, int> newOrigin = getNewOrigin(origin,
		std::pair<int, int>(sprite.getTexture()->getSize().x, sprite.getTexture()->getSize().y));
	sprite.setOrigin(newOrigin.first, newOrigin.second);
	sprite.setScale(guiScale);

	doHitBox();
}

// Specific methods
void SpriteButton::doHitBox() {
	hitBox = sprite.getGlobalBounds();
	hitBox.left += getPosition().x;
	hitBox.top += getPosition().y;
}

const sf::FloatRect& SpriteButton::getGlobalBounds()
{
	return hitBox;
}