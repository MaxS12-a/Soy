#include "pch.h"
#include "SpriteButton.h"

SpriteButton::SpriteButton(float x, float y, 
	const std::string& idleTextureFile, const std::string& pressedTextureFile,
	const sf::Vector2f& guiScale, const sf::Vector2f& origin, const sf::Vector2u& windowResolution,
	sf::Sound& hoverSound, sf::Sound& pressedSound, const sf::Vector2f& scaleOnHover)
	: Button(x, y, guiScale, origin, windowResolution, hoverSound, pressedSound), 
	scaleOnHover(scaleOnHover)
{
	idleTexture = new sf::Texture();
	if (!idleTexture->loadFromFile(idleTextureFile)) LOG_CRITICAL("Could not load {0}", idleTextureFile);

	if (pressedTextureFile.empty())
		pressedTexture = nullptr;
	else {
		pressedTexture = new sf::Texture();
		if (!pressedTexture->loadFromFile(pressedTextureFile)) LOG_CRITICAL("Could not load {0}", pressedTextureFile);
	}

	sprite.setTexture(*idleTexture);

	create(windowResolution, guiScale);
}

SpriteButton::~SpriteButton()
{
	delete idleTexture;
	delete pressedTexture;
}

bool SpriteButton::update(const MouseState& mouseState)
{
	if (Button::update(mouseState))
		return true;

	if (pressedTexture) {
		if (hover && mouseState.mousePressedLeft) {
			if (sprite.getTexture() == idleTexture)
				sprite.setTexture(*pressedTexture);
		}
		else if (sprite.getTexture() == pressedTexture) sprite.setTexture(*idleTexture);
	}

	if (scaleOnHover.x != 1 || scaleOnHover.y != 1) {
		if (hover) {
			if (sprite.getScale().x == guiScale.x && sprite.getScale().y == guiScale.y)
				sprite.setScale(scaleOnHover.x * guiScale.x, scaleOnHover.y * guiScale.y);

		}
		else if (sprite.getScale().x != guiScale.x || sprite.getScale().y != guiScale.y)
			sprite.setScale(guiScale);
	}

	return false;
}

void SpriteButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

void SpriteButton::doHitBox() {
	hitBox = sprite.getGlobalBounds();
	hitBox.left += getPosition().x;
	hitBox.top += getPosition().y;
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
