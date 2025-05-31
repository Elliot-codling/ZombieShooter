#pragma once
#include "SFML/Graphics.hpp"

class SFML_LoreScreen : public sf::Drawable
{
public:
	SFML_LoreScreen(std::string menuFileName, int windowWidth, int windowHeight);
	~SFML_LoreScreen();

	bool update(sf::Time elapsedTime);
	void reset();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::string m_loreString;
	std::string m_loreStringUncompleted;
	sf::Text m_loreText;

	sf::Font m_gameFont;
	int letterNum = 0;

	int framesPassed = 0;

};

