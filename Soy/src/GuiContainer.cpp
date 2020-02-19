#include "pch.h"
#include "GuiContainer.h"

// Constructos & destructors
GuiContainer::GuiContainer(float x, float y, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale,
	int distItI)
	: GuiItem(x, y, { 0.5, 0.5 }, windowResolution, guiScale), distItI(distItI)
{
	create(windowResolution, guiScale);
}

GuiContainer::~GuiContainer()
{
	for (auto i : items)
		delete i.second;
}

// GL methods
bool GuiContainer::update(const MouseState& mouseState)
{
	selected = -1;
	for (auto i : items) {
		if (i.second->update(mouseState)) 
			selected = i.first;
		
		if (i.second->update()) 
			selected = i.first;
	}
	if (selected != -1) return true;
	return false;
}

void GuiContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	for (auto i : items)
		target.draw(*i.second, states);
}

void GuiContainer::create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale)
{
	this->windowResolution = windowResolution;
	this->guiScale = guiScale;

	setPosition(x / 1920 * windowResolution.x, y / 1080 * windowResolution.y);

	int distItI = this->distItI * guiScale.y;

	int actualPos = 0;
	for (auto i : items) {
		i.second->create(windowResolution, guiScale);
		i.second->move(0, actualPos);
		i.second->moveHitBox(getPosition().x , getPosition().y + actualPos);
		actualPos += i.second->getGlobalBounds().height + distItI * guiScale.y * windowResolution.y / 1080;
	}
}

// Specific methods
const sf::FloatRect& GuiContainer::getGlobalBounds() {
	
	int a = 0, s = 0, f = -1, l = 0;
	for (auto i : items) {
		l = i.first;
		if (f == -1) f = l;
		if (i.second->getGlobalBounds().width > a) {
			a = i.second->getGlobalBounds().width;
			s = l;
		}
	}

	globalBounds = sf::FloatRect(sf::Vector2f({ items[s]->getGlobalBounds().left, items[f]->getGlobalBounds().top }),
		sf::Vector2f({ items[s]->getGlobalBounds().width, items[l]->getGlobalBounds().top + items[l]->getGlobalBounds().height - items[f]->getGlobalBounds().top }));

	return globalBounds;
}

// Item handlers
void GuiContainer::addItem(int key, GuiItem* item)
{
	items[key] = item;
}

void GuiContainer::removeitem(int key)
{
	items.erase(key);
}

GuiItem* GuiContainer::getItem(int key)
{
	return items[key];
}

void* GuiContainer::getInfo()
{
	return new int(selected);
}