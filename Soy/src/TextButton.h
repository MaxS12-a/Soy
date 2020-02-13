#pragma once
#include "Button.h"
class TextButton :
	public Button
{
public:
	TextButton(float x, float y, const char* bname, 
		const char* fontFile, int charSize, const sf::Color& idleColor, const sf::Color& hoverColor,
		const sf::Vector2f& guiScale, Corner corner, const sf::Vector2u& windowResolution, const char* hoverSound, const char* pressedSound);

	bool update(int x, int y , bool press);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void create(sf::Vector2u windowResolution, sf::Vector2f guiScale);
private:
	sf::Font font;
	sf::Text text;
	int charSize;
	sf::Color idleColor;
	sf::Color hoverColor;
};

