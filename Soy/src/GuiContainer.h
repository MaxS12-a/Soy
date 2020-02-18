#pragma once
#include "GuiItem.h"

// A class that keep the items on a certain distance.
class GuiContainer :
	public GuiItem
{
public:
	// Constructos & destructors
	GuiContainer(float x, float y, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale, int distItI);
	virtual ~GuiContainer();

	// GL methods
	bool update(const MouseState& mouseState);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale);

	// Specific methods
	const sf::FloatRect& getGlobalBounds();

	// Item handlres
	void addItem(int key, GuiItem* item);
	void removeitem(int key);
	GuiItem* getItem(int key);

	void* getInfo();
private:
	std::map<int, GuiItem*> items;
	int selected;
	int distItI;
};

