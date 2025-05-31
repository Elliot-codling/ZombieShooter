#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
class SFML_GameMenu: public Drawable, public Transformable
{
public:
	SFML_GameMenu(std::string menuFileName, int windowWidth, int windowHeight);
	~SFML_GameMenu();

	int update(sf::Time elapsedTime);

private:
	virtual void draw(RenderTarget& target, RenderStates states) const;

	Texture m_logo;
	Sprite m_logoSprite;

	Texture m_background;
	Sprite m_backgroundSprite;
	FloatRect m_backgroundRect;

	Font m_gameFont;
	Color m_highLightTextColour;
	Color m_normalTextColour;
	Color m_normalOutlineColour;
	Color m_highLightOutlineColour;
	Vector2f m_menuItemBorder;
	std::vector<Text> m_menuText;

	enum MENU_ALIGNMENT
	{
		LEFT_JUSTIFIED,
		CENTRE_JUSTIFIED,
		RIGHT_JUSTIFIED
	};

	MENU_ALIGNMENT m_menuAlignment;
	int m_highlightIndex;

	bool m_prevDownKeyPress;
	bool m_prevUpKeyPress;
	bool m_prevReturnKeyPress;
};

