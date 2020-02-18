#pragma once
#include "State.h"

// Abstract class base for all the GuiItems
class GuiItem : public sf::Transformable, public sf::Drawable
{
public:
	// Constructors & destructors
	GuiItem(float x, float y, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale);
	virtual ~GuiItem();

	// GL methods
	virtual bool update(const MouseState& mouseState);
	virtual bool update();

	// Handler methods
	virtual void create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale) = 0;

	virtual void moveHitBox(float x, float y);

	// Basic getters
	/* Return a void p w info of some items */
	virtual void* getInfo();
	virtual const sf::Vector2f& getOrigin();
	virtual const sf::Vector2f& getBasePosition();
	virtual const sf::FloatRect& getGlobalBounds() = 0;


	// Functions
	/* Return a new origin based on the size and a % (0~1) */
	static std::pair<int, int> getNewOrigin(sf::Vector2f& origin, const std::pair<int, int>& size);

protected:
	sf::Vector2f origin;
	float x, y;
	unsigned char gID;
	sf::Vector2f guiScale;
	sf::Vector2u windowResolution;
};

