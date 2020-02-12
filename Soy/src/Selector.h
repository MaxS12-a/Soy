#pragma once
class Selector
{
public:
	Selector(int posX, int posY, int charSize, const sf::Font& textFont, sf::Color textColorIdle, sf::Color textColorHover, 
		const sf::Texture& arrowTextureL, std::vector<sf::VideoMode>* options, sf::Sound& hoverSound, sf::Sound& pressedSound, double guiScale);
	virtual ~Selector();

	void update(sf::Vector2i mousePosWindow);
	void render(sf::RenderTarget* target);
private:
	bool hover;
	std::vector<std::string> options;

	sf::Text text;
	sf::FloatRect textRect;

	sf::Color textColorIdle, textColorHover;

	sf::Sound& hoverSound;
	sf::Sound& pressedSound;

	sf::Sprite arrowSpriteL, arrowSpriteR;
	sf::FloatRect arrowRectL, arrowRectR;
};

