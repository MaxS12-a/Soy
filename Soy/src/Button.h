#pragma once
class Button
{
public:
	Button(int posX, int posY,
		const char* bname, const sf::Color& textColorIdle, const sf::Color& textColorHover, int charSize, const sf::Font& textFont,
		sf::Sound& hoverSound, sf::Sound& pressedSound);
	virtual ~Button();

	void update(sf::Vector2i mousePosWindow);
	void render(sf::RenderTarget* target);

	void press();
	const bool getHover() const;

	const sf::FloatRect getGlobalBounds() const;

private:
	sf::FloatRect* baseRect;
	sf::Text text;
	sf::Color textColorIdle, textColorHover;

	sf::Sound& hoverSound;
	sf::Sound& pressedSound;

	bool hover;
};

