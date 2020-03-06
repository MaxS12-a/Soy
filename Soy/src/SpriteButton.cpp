#include "pch.h"
#include "SpriteButton.h"

// Constructors & destructors
SpriteButton::SpriteButton(float x, float y, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale, 
	const std::string& textureFile, const sf::Vector2f& scaleOnHover, sf::Sound* hoverSound, sf::Sound* pressedSound)
	: Button(x, y, origin, windowResolution, guiScale, hoverSound, pressedSound),
	scaleOnHover(scaleOnHover), actualTexture(0)
{
	textures.push_back(new sf::Texture);
	if (!textures[actualTexture]->loadFromFile(textureFile)) LOG_CRITICAL("Could not load {0}", textureFile);

	setTexture(actualTexture);
}

SpriteButton::~SpriteButton()
{
	for (auto i : textures)
		delete i;
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
	this->windowResolution = windowResolution;
	this->guiScale = guiScale;

	setPosition(x / 1920 * windowResolution.x, y / 1080 * windowResolution.y);

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

void SpriteButton::addTexture(const std::string& textureFile)
{
	textures.push_back(new sf::Texture);
	if (!textures.back()->loadFromFile(textureFile)) LOG_CRITICAL("Could not load {0}", textureFile);
}

void SpriteButton::setTexture(int pos)
{
	actualTexture = pos;
	sprite.setTexture(*textures[actualTexture]);
	create(windowResolution, guiScale);
}

const int SpriteButton::getActualTexture()
{
	return actualTexture;
}

const sf::FloatRect& SpriteButton::getGlobalBounds()
{
	globalBounds = hitBox;
	return globalBounds;
}