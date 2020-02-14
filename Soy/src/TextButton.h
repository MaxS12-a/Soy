#pragma once
#include "Button.h"

class TextButton :
	public Button
{
public:
	TextButton(unsigned char gID, float x, float y, const std::string& name,
		const sf::Font& font, int charSize, const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Vector2f& guiScale, Corner corner, 
		const sf::Vector2u& windowResolution, bool goBold, sf::Sound& hoverSound, sf::Sound& pressedSound);
	virtual ~TextButton();

	bool update(const MouseState& mouseState);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void create(const sf::Vector2u& windowResolution,const sf::Vector2f& guiScale);
private:
	sf::Text text;
	int charSize;
	bool goBold;
	bool colorControl;
	sf::Color idleColor;
	sf::Color hoverColor;
};

