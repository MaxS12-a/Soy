#include "pch.h"
#include "Background.h"

// Constructors & destructors
Background::Background(float x, float y, const std::string& mainTextureFile, const sf::IntRect& bgTextureRect, 
	int noOfImagesLastRow, int textureChangeFreq, const sf::Vector2u& windowResolution)
	: x(x), y(y), bgTextureRect(bgTextureRect), noOfImagesLastRow(noOfImagesLastRow), textureChangeFreq(textureChangeFreq),
	textureChangeCounter(0), windowResolution(windowResolution)
{
	bgTexture = new sf::Texture();
	bgTexture->loadFromFile(mainTextureFile);

	cols = bgTexture->getSize().x / bgTextureRect.width;
	rows = bgTexture->getSize().y / bgTextureRect.height;

	bgSprite = new sf::Sprite(*bgTexture, bgTextureRect);
	bgSprite->setPosition(x, y);
	bgSprite->setScale(windowResolution.x / 1920, windowResolution.y / 1080);
}

Background::~Background()
{
	delete bgSprite;
	delete bgTexture;
	for (auto i : movSprites)
		delete i;
}

// GL methods
void Background::update()
{
	if (textureChangeFreq != -1) {
		textureChangeCounter++;
		if (textureChangeCounter == textureChangeFreq) {
			textureChangeCounter = 0;
			bgTextureRect.left += bgTextureRect.width;

			if (bgTextureRect.top >= bgTexture->getSize().y - bgTextureRect.height) {
				if (bgTextureRect.left >= bgTextureRect.width * noOfImagesLastRow) {
					bgTextureRect.left = 0;
					bgTextureRect.top = 0;
				}
			}
			else if (bgTextureRect.left >= bgTexture->getSize().x) {
				bgTextureRect.left = 0;
				bgTextureRect.top += bgTextureRect.height;
			}

			bgSprite->setTextureRect(bgTextureRect);
		}
	}

	for (auto i : movSprites)
		i->update();
}

void Background::render(sf::RenderTarget* target)
{
	target->draw(*bgSprite);

	for (auto i : movSprites)
		i->render(target);
}

// Specific methods
void Background::addBGMovSprite(BGMovSprite* movSprite)
{
	movSprites.push_back(movSprite);
}

void Background::recreate(const sf::Vector2u& windowResolution)
{
	this->windowResolution = windowResolution;
	bgSprite->setScale(windowResolution.x / 1920, windowResolution.y / 1080);
	
	for (auto i : movSprites)
		i->recreate(windowResolution);
}
