#pragma once
#include "GuiItem.h"

// Just a sprite
class GuiSprite :
	public GuiItem
{
public:
	// Constructors & destructors
	GuiSprite(float x, float y, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale, 
		const std::string& textureFile);
	virtual ~GuiSprite();

	// GL methods
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale);

	// Specific methods
	const sf::FloatRect& getGlobalBounds();

private:
	sf::Texture* texture;
	sf::Sprite sprite;
};

