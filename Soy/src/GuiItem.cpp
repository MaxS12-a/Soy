#include "pch.h"
#include "GuiItem.h"

// Constructors & destrunctors
GuiItem::GuiItem(float x, float y, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale)
	: origin(origin), x(x), y(y), guiScale(guiScale), windowResolution(windowResolution)
{
}

GuiItem::~GuiItem()
{

}

// GL methods
bool GuiItem::update() { return false; }
bool GuiItem::update(const MouseState& mouseState){	return false; }

// Handler methods
void GuiItem::moveHitBox(float x, float y) { return; }

// Basic getters
void* GuiItem::getInfo(){ return nullptr; }
const sf::Vector2f& GuiItem::getOrigin(){ return origin;}
const sf::Vector2f& GuiItem::getBasePosition(){	return sf::Vector2f(x, y); }

// Functions
std::pair<int, int> GuiItem::getNewOrigin(sf::Vector2f& origin, const std::pair<int, int>& size)
{
	return std::pair<int, int>(size.first*origin.x, size.second*origin.y);
}
