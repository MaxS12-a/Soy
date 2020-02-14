#include "pch.h"
#include "GuiItem.h"

GuiItem::GuiItem(unsigned char gID, float x, float y,const sf::Vector2f& guiScale, Corner corner, const sf::Vector2u& windowResolution)
	: corner(corner), gID(gID), x(x), y(y)
{
}

GuiItem::~GuiItem()
{

}unsigned char GuiItem::getgID()
{
	return gID;
}

std::pair<int, int> GuiItem::getNewOrigin(Corner corner, const std::pair<int, int>& size)
{
	switch (corner) {
	case Corner::TopLeft:
		return std::pair<int, int>(0, 0);
		break;
	case Corner::Top:
		return std::pair<int, int>(size.first/2, 0);
		break;
	case Corner::TopRight:
		return std::pair<int, int>(size.first, 0);
		break;
	case Corner::Left:
		return std::pair<int, int>(0, size.second/2);
		break;
	case Corner::Center:
		return std::pair<int, int>(size.first/2, size.second/2);
		break;
	case Corner::Right:
		return std::pair<int, int>(size.first, size.second/2);
		break;
	case Corner::BottomLeft:
		return std::pair<int, int>(0, size.second);
		break;
	case Corner::Bottom:
		return std::pair<int, int>(size.first / 2, size.second);
		break;
	case Corner::BottomRight:
		return std::pair<int, int>(size.first, size.second);
		break;
	default:
		return std::pair<int, int>(0, 0);
	}
}
