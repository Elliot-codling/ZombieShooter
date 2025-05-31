#include "SFML_LoreScreen.h"
#include <fstream>
#include <iostream>
#include <string>


SFML_LoreScreen::SFML_LoreScreen(std::string menuFileName, int windowWidth, int windowHeight)
{
	std::ifstream inputFile(menuFileName);

	if (inputFile.is_open())
	{
		std::string stringLine;
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			m_gameFont.loadFromFile(stringLine);		//Load font
		}

		do
		{
			std::getline(inputFile, stringLine);
			if (inputFile.good())
			{
				m_loreString += stringLine + "\n";
			}
			else
			{
				break;
			}
		} while (true);

		m_loreText.setString("");
		m_loreText.setFont(m_gameFont);
		m_loreText.setCharacterSize(40);
		m_loreText.setPosition(50, 200);
		m_loreText.setFillColor(sf::Color::Green);

		
	}
}

SFML_LoreScreen::~SFML_LoreScreen()
{
	
}


bool SFML_LoreScreen::update(sf::Time elapsedTime)
{
	if (framesPassed % 2 == 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			m_loreText.move(0, -2);

			m_loreStringUncompleted += m_loreString[letterNum];
			letterNum++;
			if (letterNum >= m_loreString.size())
			{
				return true;
			}
			m_loreStringUncompleted += m_loreString[letterNum];
			letterNum++;

			if (letterNum >= m_loreString.size())
			{
				return true;
			}

			m_loreStringUncompleted += m_loreString[letterNum];
			letterNum++;
			if (letterNum >= m_loreString.size())
			{
				return true;
			}
		}
		m_loreStringUncompleted += m_loreString[letterNum];
		letterNum++;

		m_loreText.setString(m_loreStringUncompleted);

		if (letterNum >= m_loreString.size())
		{
			return true;
		}
		
	}
	if (m_loreText.getGlobalBounds().top + m_loreText.getGlobalBounds().height >= 900)
	{
		m_loreText.move(0, -1);
	}
	

	framesPassed++;
	return false;
}

void SFML_LoreScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_loreText, states);
}


void SFML_LoreScreen::reset()
{
	framesPassed = 0;
	letterNum = 0;
	m_loreStringUncompleted = "";
	m_loreText.setString("");
	m_loreText.setPosition(50, 200);
}


