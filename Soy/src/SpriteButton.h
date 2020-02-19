#pragma once
#include "Button.h"

// A button w a sprite that scale on hover
class SpriteButton :
	public Button
{
public:
	// Constructors & destructors
	SpriteButton(float x, float y, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale, 
		const std::string& textureFile, const sf::Vector2f& scaleOnHover, sf::Sound* hoverSound, sf::Sound* pressedSound);
	virtual ~SpriteButton();

	// GL methods
	bool update(const MouseState& mouseState);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale);

	// Specific methods
	void doHitBox();

	void addTexture(const std::string& textureFile);
	void setTexture(int pos);
	const int getActualTexture();

	const sf::FloatRect& getGlobalBounds();
	
private:
	std::vector<sf::Texture*> textures;
	int actualTexture;
	sf::Sprite sprite;
	
	sf::Vector2f scaleOnHover;
};

