#pragma once
#include "Button.h"

// A text button that changes the text color on hover
class TextButton :
	public Button
{
public:
	// Constructors & destructors
	TextButton(float x, float y, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale,
		const std::string& name, const sf::Font& font, int charSize, const sf::Color& idleColor, const sf::Color& hoverColor, 
		bool goBold, sf::Sound& hoverSound, sf::Sound& pressedSound);
	virtual ~TextButton();

	// GL methods
	bool update(const MouseState& mouseState);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale);

	// Specific methods
	void doHitBox();

	/* Set the string and call create. */
	void setString(const std::string& newString);
	const sf::FloatRect& getGlobalBounds();

private:
	sf::Text text;
	int charSize;
	bool goBold;
	bool colorControler;
	sf::Color idleColor;
	sf::Color hoverColor;
};

