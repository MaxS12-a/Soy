#pragma once
#include "BGMovSprite.h"

class Background
{
public:
	Background(const std::string& mainImage);
	virtual ~Background();

	void update();
	void render(sf::RenderTarget* target);


private:

};

