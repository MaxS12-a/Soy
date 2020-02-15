#pragma once
#include "Button.h"

class TextButton :
	public Button
{
public:
	TextButton(float x, float y, const std::string& name,
		const sf::Font& font, int charSize, const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Vector2f& guiScale, const sf::Vector2f& origin,
		const sf::Vector2u& windowResolution, bool goBold, sf::Sound& hoverSound, sf::Sound& pressedSound);
	virtual ~TextButton();

	bool update(const MouseState& mouseState);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setString(const std::string& newString);

	void create(const sf::Vector2u& windowResolution,const sf::Vector2f& guiScale);
private:
	sf::Text text;
	int charSize;
	bool goBold;
	bool colorControler;
	sf::Color idleColor;
	sf::Color hoverColor;
};

