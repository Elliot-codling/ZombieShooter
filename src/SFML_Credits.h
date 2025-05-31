#pragma once
#include "SFML/Graphics.hpp"
class SFML_Credits : public sf::Drawable
{
public:
	SFML_Credits(std::string menuFileName, int windowWidth, int windowHeight);
	~SFML_Credits();

	bool update(sf::Time elapsedTime);
	void resetCredits();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture m_logo;
	sf::Sprite m_logoSprite;
	sf::FloatRect m_backgroundRect;

	sf::Font m_gameFont;

	std::string m_creditsString;
	sf::Text m_creditsText;


	sf::Vector2f m_menuItemBorder;
	std::vector<sf::Text> m_menuText;

	enum MENU_ALIGNMENT
	{
		LEFT_JUSTIFIED,
		CENTRE_JUSTIFIED,
		RIGHT_JUSTIFIED
	};

	MENU_ALIGNMENT m_menuAlignment;
	int m_highlightIndex;

	int m_offset = 2;
	int m_windowWidth;
	int m_windowHeight;
};

