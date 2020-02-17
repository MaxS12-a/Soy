#pragma once
#include "GuiItem.h"

class GuiSprite :
	public GuiItem
{
public:
	GuiSprite(float x, float y, const std::string& textureFile, const sf::Vector2f& guiScale, const sf::Vector2f& origin, const sf::Vector2u& windowResolution);
	virtual ~GuiSprite();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	const sf::FloatRect& getGlobalBounds();

	void create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale);
private:
	sf::Texture* texture;
	sf::Sprite sprite;
};

