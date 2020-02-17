#pragma once
#include "Button.h"

class SpriteButton :
	public Button
{
public:
	SpriteButton(float x, float y, const std::string& idleTextureFile, const std::string& pressedTextureFile, 
		const sf::Vector2f& guiScale, const sf::Vector2f& origin, const sf::Vector2u& windowResolution,
		sf::Sound& hoverSound, sf::Sound& pressedSound, const sf::Vector2f& scaleOnHover);
	virtual ~SpriteButton();

	bool update(const MouseState& mouseState);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void doHitBox();

	const sf::FloatRect& getGlobalBounds();

	void create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale);
private:
	sf::Texture* idleTexture;
	sf::Texture* pressedTexture;
	sf::Sprite sprite;
	
	sf::Vector2f scaleOnHover;
	sf::Vector2f guiScale;
};

