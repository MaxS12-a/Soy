#pragma once
class GuiItem : public sf::Transformable, public sf::Drawable
{
public:
	enum Corner {TopLeft, Top, TopRight, Left, Center, Right, BottomLeft, Bottom, BottomRight};

	GuiItem(float x, float y, const sf::Vector2f& guiScale, Corner corner, const sf::Vector2u& windowResolution);
	virtual ~GuiItem();

	virtual bool update(int mousex, int mousey, bool press) = 0;

	virtual void create(sf::Vector2u windowResolution, sf::Vector2f guiScale) = 0;
	virtual void setVolume(float volume) = 0;

	static std::pair<int, int> getNewOrigin(Corner corner, const std::pair<int, int>& size);
protected:
	Corner corner;
	float x, y;
};

