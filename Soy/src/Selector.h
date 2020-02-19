#pragma once
#include "TextButton.h"
#include "SpriteButton.h"

// A text, one RArrow and a LArrow. When one arrow get pressed the text changes. When the text is pressed return the string on it.
class Selector :
	public GuiItem
{
public:
	// Constructors & destructors
	Selector(float x, float y, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale,
		int distItI, std::vector<std::string>* options, int baseOption,
		/* Text */
		const sf::Font& font, int charSize, const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& outlineColor, int outlineThickness, sf::Sound* hoverSoundText, sf::Sound* pressedSoundText,
		/* Arrows */
		const std::string& textureFile, const sf::Vector2f& scaleOnHover, sf::Sound* hoverSoundButtons, sf::Sound* pressedSoundButtons);
	virtual ~Selector();

	// GL methods
	bool update(const MouseState& mouseState);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale);

	// Specific methods
	void doButtons();

	void moveHitBox(float x, float y);
	const sf::FloatRect& getGlobalBounds();

	void* getInfo();

private:
	TextButton* text;
	SpriteButton* buttonL;
	SpriteButton* buttonR;
	std::vector<std::string>* options;
	int option;
	int distItI;
	sf::Vector2f hitBoxPos;
};

