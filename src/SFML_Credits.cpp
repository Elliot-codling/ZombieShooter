#include "SFML_Credits.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

SFML_Credits::SFML_Credits(std::string menuFileName, int windowWidth, int windowHeight):
m_windowWidth(windowWidth),
m_windowHeight(windowHeight)
{
	std::ifstream inputFile(menuFileName);

	if (inputFile.is_open())
	{
		std::string stringLine;

		//Read the 1st line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//Load the file and set the texture
			m_logo.loadFromFile(stringLine);
			m_logoSprite.setTexture(m_logo);

			//Set the origin, texture rect and the position
			sf::Vector2u textureSize = m_logo.getSize();
			m_logoSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_logoSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
			m_logoSprite.setPosition(windowWidth / 2, windowHeight + 50);

			m_backgroundRect.left = -static_cast<float>(textureSize.x / 2);
			m_backgroundRect.top = -static_cast<float>(textureSize.y / 2);
			m_backgroundRect.width = textureSize.x;
			m_backgroundRect.height = textureSize.y;
		}
		else
		{
			std::cout << "Cannot read file!.\n";
		}


		//Now read the second line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			m_gameFont.loadFromFile(stringLine);
		}

		//Now read the third line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			m_creditsString += stringLine + "\n";
		}

		//Now read the fourth line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			m_creditsString += stringLine + "\n";
		}

		//Now read the 5th line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			m_creditsString += stringLine + "\n";
		}

		//Now read the 6th line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			m_creditsString += stringLine + "\n";
		}

		//Now read the 7th line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			m_creditsString += stringLine + "\n";
		}

		//Now read the 8th line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			m_creditsString += stringLine + "\n";
		}

		//Now read the 9th line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			m_creditsString += stringLine + "\n";
		}

		m_creditsText.setString(m_creditsString);
		m_creditsText.setFont(m_gameFont);
		m_creditsText.setCharacterSize(80);
		m_creditsText.setFillColor(sf::Color::Blue);
		m_creditsText.setOutlineColor(sf::Color::White);
		m_creditsText.setOutlineThickness(5);
		m_creditsText.setPosition((windowWidth / 2) - m_creditsText.getGlobalBounds().width / 2, windowHeight + 400);

	}
	inputFile.close();

}

SFML_Credits::~SFML_Credits()
{
	m_menuText.clear();
}

void SFML_Credits::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//states.transform *= getTransform();
	target.draw(m_logoSprite, states);
	target.draw(m_creditsText, states);

	for (std::size_t count = 0; count < m_menuText.size(); count++)
	{
		target.draw(m_menuText[count], states);
	}
}

bool SFML_Credits::update(sf::Time elapsedTime)
{
	if (m_creditsText.getPosition().y + m_creditsText.getGlobalBounds().height <= -50)
	{
		return true;
	}
	m_logoSprite.move(0, -m_offset);
	m_creditsText.move(0, -m_offset);

	return  false;
}

void SFML_Credits::resetCredits()
{
	m_logoSprite.setPosition(m_windowWidth / 2, m_windowHeight + 50);
	m_creditsText.setPosition((m_windowWidth / 2) - m_creditsText.getGlobalBounds().width / 2, m_windowHeight + 400);

}


