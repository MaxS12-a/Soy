#pragma once
#include "Button.h"

// A slider with a progress bar
class GuiSlider :
	public Button
{
public:
	// Constructors & destructors
	GuiSlider(float x, float y, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale,
		const std::string& sliderBarEmptyTextureFile, const std::string& sliderBarFilledTextureFile, const std::string& sliderItemTextureFile,
		const sf::Color& hoverColor, std::vector<std::string>* options, int baseOption, const sf::Font& font, 
		int charSize, const sf::Color& textColor, const sf::Color& outlineColor, int outlineThickness, 
		sf::Sound* hoverSound, sf::Sound* pressedSound);
	virtual ~GuiSlider();

	// GL methods
	bool update(const MouseState& mouseState);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale);

	// Specific methods
	void doHitBox();
	void moveHitBox(float x, float y);

	const sf::FloatRect& getGlobalBounds();

	void* getInfo();

private:
	sf::Texture* sliderBarEmptyTexture;
	sf::Texture* sliderBarFilledTexture;
	sf::Texture* sliderItemTexture;

	sf::Sprite sliderBarEmpty;
	sf::Sprite sliderBarFilled;
	sf::Sprite sliderItem;

	sf::IntRect filledRect, emptyRect;
	sf::Color hoverColor;

	sf::Text text;
	std::vector<std::string>* options;
	int option, optionsSize;

	bool pressed;
	int initialMousePosWindowx;

	sf::Vector2f hitBoxPos;
	sf::FloatRect mouseBounds;

	// Private methods
	void testOption();
	void updateTextureRects();
	void setTextPos();
};

