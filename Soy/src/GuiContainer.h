#pragma once
#include "GuiItem.h"
class GuiContainer :
	public GuiItem
{
public:
	GuiContainer(float x, float y, const sf::Vector2f& guiScale, const sf::Vector2u& windowResolution, int distOtO);
	virtual ~GuiContainer();

	bool update(const MouseState& mouseState);

	void create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	const sf::FloatRect& getGlobalBounds();

	void addItem(int key, GuiItem* item);
	void removeitem(int key);
	GuiItem* getItem(int key);

	void* getInfo();
private:
	std::map<int, GuiItem*> items;
	int selected;
	int distItI;
};

