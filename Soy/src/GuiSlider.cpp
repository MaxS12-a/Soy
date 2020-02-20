#include "pch.h"
#include "GuiSlider.h"

// Constructors & destructors
GuiSlider::GuiSlider(float x, float y, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale,
	const std::string& sliderBarEmptyTextureFile, const std::string& sliderBarFilledTextureFile, const std::string& sliderItemTextureFile,
	const sf::Color& hoverColor, std::vector<std::string>* options, int baseOption, const sf::Font& font,
	int charSize, const sf::Color& textColor, const sf::Color& outlineColor, int outlineThickness,
	sf::Sound* hoverSound, sf::Sound* pressedSound)
	:Button(x, y, origin, windowResolution, guiScale, hoverSound, pressedSound), hoverColor(hoverColor), 
	options(options), option(baseOption), optionsSize(options->size()), pressed(false), hitBoxPos({ 0,0 })
{
	sliderBarEmptyTexture = new sf::Texture();
	sliderBarFilledTexture = new sf::Texture();
	sliderItemTexture = new sf::Texture();

	sliderBarEmptyTexture->loadFromFile(sliderBarEmptyTextureFile);
	sliderBarFilledTexture->loadFromFile(sliderBarFilledTextureFile);
	sliderItemTexture->loadFromFile(sliderItemTextureFile);

	text.setCharacterSize(charSize);
	text.setFont(font);
	text.setFillColor(textColor);
	text.setOutlineColor(outlineColor);
	text.setOutlineThickness(outlineThickness);
	
	text.setString((*options)[option]);

	emptyRect.top = 0;
	emptyRect.height = sliderBarEmptyTexture->getSize().y;

	filledRect.left = 0;
	filledRect.top = 0;
	filledRect.height = sliderBarEmptyTexture->getSize().y;

	sliderBarEmpty.setTexture(*sliderBarEmptyTexture);
	sliderBarFilled.setTexture(*sliderBarFilledTexture);

	sliderItem.setTexture(*sliderItemTexture);

	initialMousePosWindowx = 0;

	create(windowResolution, guiScale);
}

GuiSlider::~GuiSlider()
{
	delete sliderBarEmptyTexture;
	delete sliderBarFilledTexture;
	delete sliderItemTexture;
	delete options;
}

// GL Methods
bool GuiSlider::update(const MouseState& mouseState)
{
	if (Button::update(mouseState)) pressed = true;

	if (hover) {
		if(sliderItem.getColor() == sf::Color::White)
			sliderItem.setColor(hoverColor);
	}
	else if(sliderItem.getColor() == hoverColor )
		sliderItem.setColor(sf::Color::White);

	if (pressed) {
		if (mouseBounds.contains(mouseState.mousePosWindow.x, mouseState.mousePosWindow.y)) {
			if (initialMousePosWindowx == 0) {
				initialMousePosWindowx = mouseState.mousePosWindow.x;
			}
			else {
				int dif = mouseState.mousePosWindow.x - initialMousePosWindowx;
				initialMousePosWindowx = mouseState.mousePosWindow.x;
				sliderItem.move(dif, 0);

				if (sliderItem.getPosition().x < 0)
					sliderItem.setPosition(0, 0);
				else if (sliderItem.getPosition().x > sliderBarFilledTexture->getSize().x* windowResolution.x / 1920.f * guiScale.x)
				{
					sliderItem.setPosition(sliderBarFilledTexture->getSize().x * (windowResolution.x / 1920.f) * guiScale.x, 0);
				}

				testOption();
				updateTextureRects();
				doHitBox();
				setTextPos();
			}
			
			
		} else {
			pressed = false;
		}
	}
	else {
		initialMousePosWindowx = 0;
	}

	if (pressed && mouseState.mouseReleasedLeft) {
		pressed = false;
		return true;
	}
	return false;	
}

void GuiSlider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sliderBarEmpty, states);
	target.draw(sliderBarFilled, states);
	target.draw(sliderItem, states);
	target.draw(text, states);
}

void GuiSlider::create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale)
{
	this->windowResolution = windowResolution;
	this->guiScale = guiScale;

	setPosition(x / 1920.f * windowResolution.x, y / 1080.f * windowResolution.y);

	move((-origin.x)*sliderBarEmptyTexture->getSize().x / 1920.f * windowResolution.x, 
		(-origin.y)*sliderBarEmptyTexture->getSize().y / 1080.f * windowResolution.y);

	text.setScale(guiScale);

	sliderBarEmpty.setScale(guiScale);
	sliderBarFilled.setScale(guiScale);
	sliderItem.setScale(guiScale);

	sliderItem.setPosition((sliderBarEmptyTexture->getSize().x * (windowResolution.x / 1920.f) * guiScale.x) / optionsSize * option, 0);

	updateTextureRects();

	sliderBarFilled.setPosition(0, 0);

	setTextPos();

	sf::Vector2f o = { 0.5, 0 };
	std::pair<int, int> nO = getNewOrigin(o, std::make_pair(sliderItem.getGlobalBounds().width, sliderItem.getGlobalBounds().height));
	sliderItem.setOrigin(nO.first, nO.second);

	doHitBox();

	getGlobalBounds();
}

// Specific methods
void GuiSlider::doHitBox()
{
	hitBox = sliderItem.getGlobalBounds();
	hitBox.left += getPosition().x + hitBoxPos.x;
	hitBox.top += hitBoxPos.y - sliderItem.getGlobalBounds().height / 2;
}

void GuiSlider::moveHitBox(float x, float y)
{
	hitBoxPos.x = x;
	hitBoxPos.y = y;
	doHitBox();
}

const sf::FloatRect& GuiSlider::getGlobalBounds()
{
	globalBounds.left = hitBox.left - sliderItem.getGlobalBounds().left;
	globalBounds.top = hitBox.top;
	globalBounds.width = sliderBarEmptyTexture->getSize().x * (windowResolution.x / 1920.f);
	globalBounds.height = hitBox.height;

	mouseBounds.left = globalBounds.left - sliderItem.getGlobalBounds().width;
	mouseBounds.top = globalBounds.top - 10;
	mouseBounds.width = globalBounds.width + 2 * sliderItem.getGlobalBounds().width;
	mouseBounds.height = globalBounds.height + 20;

	return globalBounds;
}

void* GuiSlider::getInfo()
{
	return (void*)new std::string((*options)[option]);
}

// Private methods
void GuiSlider::testOption()
{
	float a = sliderItem.getPosition().x / ((sliderBarFilledTexture->getSize().x * windowResolution.x / 1920.f * guiScale.x) / (optionsSize - 1));
	option = (int)a;
	text.setString((*options)[option]);
}

void GuiSlider::updateTextureRects()
{
	if (sliderItem.getPosition().x > 0)
		filledRect.width = sliderItem.getPosition().x;
	else
		filledRect.width = 0;

	emptyRect.left = filledRect.width;
	emptyRect.width = sliderBarEmptyTexture->getSize().x - emptyRect.left;

	sliderBarEmpty.setTextureRect(emptyRect);
	sliderBarFilled.setTextureRect(filledRect);

	sliderBarEmpty.setPosition(sliderBarFilled.getGlobalBounds().width, 0);
}

void GuiSlider::setTextPos()
{
	text.setPosition(0, 0);
	text.setPosition(sliderItem.getPosition().x - text.getPosition().x, -text.getPosition().y);

	sf::Vector2f o(0.5, 0);
	std::pair<int, int> nO(text.getGlobalBounds().width, text.getGlobalBounds().height);
	nO = getNewOrigin(o, nO);
	text.setOrigin(nO.first, nO.second);
}