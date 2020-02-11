#pragma once
class Button
{
public:
	Button(int posX, int posY, int width, int height, bool colisionBoxFRectTText, const sf::Color& buttonColorIdle, const sf::Color& buttonColorHover,
		const char* bname, const sf::Color& textColorIdle, const sf::Color& textColorHover, int charSize, const sf::Font& textFont,
		int borderSize, const sf::Color& borderColor, sf::Sound& hoverSound, sf::Sound& pressedSound);
	virtual ~Button();

	void update(sf::Vector2i mousePosWindow);
	void render(sf::RenderTarget* target);

	void press();
	const bool getHover() const;
private:
	sf::RectangleShape buttonRect;
	sf::Color buttonColorIdle, buttonColorHover;
	sf::FloatRect* baseRect;

	sf::Text text;
	sf::Color textColorIdle, textColorHover;

	sf::RectangleShape borderRect;

	sf::Sound& hoverSound;
	sf::Sound& pressedSound;

	bool hover;
};

