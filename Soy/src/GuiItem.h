#pragma once
#include "State.h"

class GuiItem : public sf::Transformable, public sf::Drawable
{
public:
	GuiItem(float x, float y, const sf::Vector2f& guiScale, const sf::Vector2f& origin, const sf::Vector2u& windowResolution);
	virtual ~GuiItem();

	virtual bool update(const MouseState& mouseState);
	virtual bool update();

	virtual void create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale) = 0;

	virtual void moveHitBox(float x, float y);

	virtual void* getInfo();
	virtual const sf::Vector2f& getOrigin();
	virtual const sf::Vector2f& getBasePosition();
	virtual const sf::FloatRect& getGlobalBounds() = 0;

	static std::pair<int, int> getNewOrigin(sf::Vector2f& origin, const std::pair<int, int>& size);
protected:
	sf::Vector2f origin;
	float x, y;
	unsigned char gID;
	sf::Vector2f guiScale;
	sf::Vector2u windowResolution;
};

