#pragma once
#include "Button.h"

// Just a checkbox button
class GuiCheckBox :
	public Button
{
public:
	// Constructors & destructors
	GuiCheckBox(float x, float y, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale,
		const std::string& textureFile, const sf::IntRect& baseTextureRect, const sf::Vector2f& scaleOnHover,
		sf::Sound* hoverSound, sf::Sound* pressedSound);
	virtual ~GuiCheckBox();

	// GL methods
	bool update(const MouseState& mouseState);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale);

	// Specific methods
	void doHitBox();

	const sf::FloatRect& getGlobalBounds();
private:
	sf::Texture* texture;
	sf::IntRect textureRect;
	sf::Sprite sprite;

	sf::Vector2f scaleOnHover;

	bool marked;
};

