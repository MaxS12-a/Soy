#pragma once
#include "Button.h"

// A button w a sprite that scale on hover
class SpriteButton :
	public Button
{
public:
	// Constructors & destructors
	SpriteButton(float x, float y, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale, 
		const std::string& textureFile, const sf::Vector2f& scaleOnHover, sf::Sound& hoverSound, sf::Sound& pressedSound);
	virtual ~SpriteButton();

	// GL methods
	bool update(const MouseState& mouseState);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale);

	// Specific methods
	void doHitBox();

	const sf::FloatRect& getGlobalBounds();
	
private:
	sf::Texture* idleTexture;
	sf::Sprite sprite;
	
	sf::Vector2f scaleOnHover;
	sf::Vector2f guiScale;
};

