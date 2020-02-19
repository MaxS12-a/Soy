#pragma once
#include "BGMovSprite.h"

// Background class
class Background
{
public:
	// Constructors & destructors
	Background(float x, float y, const std::string& mainTextureFile, const sf::IntRect& bgTextureRect, 
		int noOfImagesLastRow, int textureChangeFreq, const sf::Vector2u& windowResolution);
	virtual ~Background();

	// GL methods
	void update();
	void render(sf::RenderTarget* target);

	// Specific methods
	void addBGMovSprite(BGMovSprite* movSprites);
	void recreate(const sf::Vector2u& windowResolution);
private:
	float x, y;
	sf::Vector2u windowResolution;

	sf::Texture* bgTexture;
	sf::IntRect bgTextureRect;
	int noOfImagesLastRow, cols, rows, textureChangeFreq, textureChangeCounter;
	sf::Sprite* bgSprite;
	
	std::vector<BGMovSprite*> movSprites;
};

