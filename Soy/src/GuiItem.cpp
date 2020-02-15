#include "pch.h"
#include "GuiItem.h"

GuiItem::GuiItem(float x, float y,const sf::Vector2f& guiScale, const sf::Vector2f& origin, const sf::Vector2u& windowResolution)
	: origin(origin),  x(x), y(y), guiScale(guiScale), windowResolution(windowResolution)
{
}

GuiItem::~GuiItem()
{

}
bool GuiItem::update(const MouseState& mouseState){	return false; }
bool GuiItem::update(){	return false; }

void* GuiItem::getInfo()
{
	return nullptr;
}

std::pair<int, int> GuiItem::getNewOrigin(sf::Vector2f& origin, const std::pair<int, int>& size)
{
	return std::pair<int, int>(size.first*origin.x, size.second*origin.y);
}
