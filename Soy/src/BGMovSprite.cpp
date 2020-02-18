#include "pch.h"
#include "BGMovSprite.h"

// Constructors & destructors
BGMovSprite::BGMovSprite(const std::string& textureFile, const sf::IntRect& baseTextureRect, int rects, int textureChangeFreq,
	int spawnFreq, const sf::IntRect& spawnArea, int lifeTime, sf::Vector2f movDir, const sf::Vector2u& windowSize)
	: baseTextureRect(baseTextureRect), rects(rects), textureChangeFreq(textureChangeFreq), spawnFreq(spawnFreq), spawnCounter(spawnFreq - 1), 
	spawnArea(spawnArea),lifeTime(lifeTime), movDir(movDir), windowSize(windowSize)
{
	texture = new sf::Texture();
	texture->loadFromFile(textureFile);
}

BGMovSprite::~BGMovSprite()
{
	for (auto i : sprites)
		delete i.first;
	delete texture;
}

// GL methods
void BGMovSprite::update()
{
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i].first->move(movDir.x * windowSize.x / 1920, movDir.y * windowSize.y / 1080);
		
		if (sprites[i].second % textureChangeFreq == 0) {
			textureRect = sprites[i].first->getTextureRect();

			textureRect.left += baseTextureRect.width;
			if (textureRect.left + textureRect.width >= texture->getSize().x)
				textureRect.left = 0;

			sprites[i].first->setTextureRect(textureRect);
		}

		sprites[i].second++;
		if (sprites[i].second > lifeTime) {
			delete sprites[i].first;
			sprites.erase(sprites.begin() + i);
		}
	}

	spawnCounter++;
	if (spawnCounter == spawnFreq) {
		spawnCounter = 0;
		sprites.push_back(std::make_pair(new sf::Sprite(*texture, baseTextureRect), 0));
		sprites.back().first->setPosition(
			rand() % (spawnArea.width * windowSize.x / 1920) + (spawnArea.left * windowSize.x / 1920),
			rand() % (spawnArea.height * windowSize.y / 1080) + (spawnArea.top * windowSize.y / 1080)
		);
		sprites.back().first->setScale(windowSize.x/1920, windowSize.y/1080);
	}

}

void BGMovSprite::render(sf::RenderTarget* target)
{
	for (auto i : sprites)
		target->draw(*i.first);
}

void BGMovSprite::recreate(const sf::Vector2u& windowSize) 
{	
	for (auto i : sprites) {
		i.first->setPosition(
			i.first->getPosition().x / this->windowSize.x * windowSize.x,
			i.first->getPosition().y / this->windowSize.y * windowSize.y);
		i.first->setScale(windowSize.x / 1920, windowSize.y / 1080);
		
	}

	this->windowSize = windowSize;
}