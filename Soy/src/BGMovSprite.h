#pragma once

// A Sprite that simply moves and change texture on the background
class BGMovSprite
{
public:
	// Constructos & destructors
	BGMovSprite(const std::string& textureFile, const sf::IntRect& baseTextureRect, int rects, int textureChangeFreq, 
		int spawnFreq, const sf::IntRect& spawnArea, int lifeTime, sf::Vector2f movDir, const sf::Vector2u& windowSize);
	virtual ~BGMovSprite();

	// GL methods
	void update();
	void render(sf::RenderTarget* target);

	void recreate(const sf::Vector2u& windowSize);

private:
	std::vector<std::pair<sf::Sprite*, int>> sprites;

	sf::Texture* texture;
	sf::IntRect baseTextureRect;
	sf::IntRect textureRect;
	int rects;
	int textureChangeFreq;

	int spawnFreq, spawnCounter;
	sf::IntRect spawnArea;
	int lifeTime;

	sf::Vector2f movDir;

	sf::Vector2u windowSize;
};

