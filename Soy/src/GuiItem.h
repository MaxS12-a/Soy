#pragma once
#include "State.h"

class GuiItem : public sf::Transformable, public sf::Drawable
{
public:
	enum Corner {TopLeft, Top, TopRight, Left, Center, Right, BottomLeft, Bottom, BottomRight};

	GuiItem(unsigned char gID,float x, float y, const sf::Vector2f& guiScale, Corner corner, const sf::Vector2u& windowResolution);
	virtual ~GuiItem();

	virtual bool update(const MouseState& mouseState) = 0;

	virtual void create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale) = 0;

	virtual unsigned char getgID();

	static std::pair<int, int> getNewOrigin(Corner corner, const std::pair<int, int>& size);
protected:
	Corner corner;
	float x, y;
	unsigned char gID;
};

