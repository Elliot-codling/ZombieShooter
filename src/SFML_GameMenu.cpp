#include "SFML_GameMenu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

SFML_GameMenu::SFML_GameMenu(std::string menuFileName, int windowWidth, int windowHeight)
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
			m_background.loadFromFile(stringLine);
			m_backgroundSprite.setTexture(m_background);

			//Set the origin, texture rect and the position
			Vector2u textureSize = m_background.getSize();
			m_backgroundSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_backgroundSprite.setTextureRect(IntRect(0, 0, textureSize.x, textureSize.y));
			m_backgroundSprite.setPosition(0, 0);

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
			//Set the texture and sprite
			m_logo.loadFromFile(stringLine);
			m_logoSprite.setTexture(m_logo);

			Vector2u textureSize = m_logo.getSize();
			m_logoSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_logoSprite.setTextureRect(IntRect(0, 0, textureSize.x, textureSize.y));
			m_logoSprite.setPosition(0, m_background.getSize().y / 2 * 0.9f);


		}
		//Now read the third line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			m_gameFont.loadFromFile(stringLine);
			

		}
		std::string redString;
		std::string greenString;
		std::string blueString;

		int redInt;
		int greenInt;
		int blueInt;

		//Now read the fourth line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			//Convert to int
			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			//Set the values to m_normalTextColour
			m_normalTextColour = Color(redInt, greenInt, blueInt);
		}

		//Now read the 5th line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			//Convert to int
			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			//Set the values to m_normalTextColour
			m_normalOutlineColour = Color(redInt, greenInt, blueInt);
		}

		//Now read the 6th line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			//Convert to int
			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			//Set the values to m_normalTextColour
			m_highLightTextColour = Color(redInt, greenInt, blueInt);
		}

		//Now read the 7th line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			//Convert to int
			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			//Set the values to m_normalTextColour
			m_highLightOutlineColour = Color(redInt, greenInt, blueInt);
		}

		std::string xBorderString;
		std::string yBorderString;

		int xBorderInt;
		int yBorderInt;

		//Read the 8th line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> xBorderString;
			stringStream >> yBorderString;

			xBorderInt = std::stoi(xBorderString);
			yBorderInt = std::stoi(yBorderString);

			//Set the values to m_menuItemBorder
			m_menuItemBorder.x = xBorderInt;
			m_menuItemBorder.y = yBorderInt;
		}

		m_menuAlignment = CENTRE_JUSTIFIED;
		//Read the 9th line
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			if (!std::strcmp(stringLine.c_str(), "LEFT_JUSTIFIED"))
			{
				m_menuAlignment = LEFT_JUSTIFIED;
			}
			else if (!std::strcmp(stringLine.c_str(), "CENTRE_JUSTIFIED"))
			{
				m_menuAlignment = CENTRE_JUSTIFIED;
			}
			else if (!std::strcmp(stringLine.c_str(), "RIGHT_JUSTIFIED"))
			{
				m_menuAlignment = RIGHT_JUSTIFIED;
			}
		}


		sf::Text start;
		start.setFont(m_gameFont);
		start.setCharacterSize(50);
		start.setStyle(sf::Text::Bold);
		start.setFillColor(m_normalTextColour);
		start.setOutlineColor(m_normalOutlineColour);
		start.setOutlineThickness(1.0f);

		Vector2f textPos;


		if (m_menuAlignment == CENTRE_JUSTIFIED)
		{
			textPos.x = m_backgroundRect.left + m_backgroundRect.width / 2;
			textPos.y = m_backgroundRect.top + m_menuItemBorder.y;
		}
		else if (m_menuAlignment == LEFT_JUSTIFIED)
		{
			textPos.x = m_backgroundRect.left + m_menuItemBorder.x;
			textPos.y = m_backgroundRect.top + m_menuItemBorder.y;
		}
		else if (m_menuAlignment == RIGHT_JUSTIFIED)
		{
			textPos.x = m_backgroundRect.left + m_backgroundRect.width - m_menuItemBorder.x;
			textPos.y = m_backgroundRect.top + m_menuItemBorder.y;
		}
		



		
		do
		{
			std::getline(inputFile, stringLine);
			if (inputFile.good())
			{
				start.setPosition(textPos.x, textPos.y);

				start.setString(stringLine);

				FloatRect textBox = start.getLocalBounds();
				if (m_menuAlignment == CENTRE_JUSTIFIED)
				{
					start.setOrigin(textBox.width / 2, textBox.height / 2);
				}
				else if (m_menuAlignment == LEFT_JUSTIFIED)
				{
					start.setOrigin(0, textBox.height / 2);
				}
				else if (m_menuAlignment == RIGHT_JUSTIFIED)
				{
					start.setOrigin(textBox.width, textBox.height / 2);
				}
				

				m_menuText.push_back(start);

				textPos.y += start.getLocalBounds().height * 1.2f;
			}
			else
			{
				break;
			}
		} while (true);

		m_highlightIndex = 0;
		m_menuText[m_highlightIndex].setFillColor(m_highLightTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_highLightOutlineColour);

		m_prevDownKeyPress = true;
		m_prevUpKeyPress = true;
		m_prevReturnKeyPress = true;

		inputFile.close();

	}


	
	
}

SFML_GameMenu::~SFML_GameMenu()
{
	m_menuText.clear();
}

void SFML_GameMenu::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_backgroundSprite, states);
	target.draw(m_logoSprite, states);

	for (std::size_t count = 0; count < m_menuText.size(); count++)
	{
		target.draw(m_menuText[count], states);
	}
}

int SFML_GameMenu::update(sf::Time elapsedTime)
{
	bool m_currentDownKeyPress = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	bool m_currentUpKeyPress = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool m_currentReturnKeyPress = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);

	if (m_currentDownKeyPress && !m_prevDownKeyPress)
	{
		m_menuText[m_highlightIndex].setFillColor(m_normalTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_normalOutlineColour);

		m_highlightIndex++;
		m_highlightIndex = m_highlightIndex % m_menuText.size();

		m_menuText[m_highlightIndex].setFillColor(m_highLightTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_highLightOutlineColour);
	}
	else if (m_currentUpKeyPress && !m_prevUpKeyPress)
	{
		m_menuText[m_highlightIndex].setFillColor(m_normalTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_normalOutlineColour);

		m_highlightIndex--;
		if (m_highlightIndex < 0)
		{
			m_highlightIndex = m_highlightIndex + m_menuText.size();
		}

		m_menuText[m_highlightIndex].setFillColor(m_highLightTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_highLightOutlineColour);
	}

	m_prevDownKeyPress = m_currentDownKeyPress;
	m_prevUpKeyPress = m_currentUpKeyPress;

	bool hasSelected = false;

	if (m_currentReturnKeyPress && !m_prevReturnKeyPress)
	{
		hasSelected = true;
	}
	m_prevReturnKeyPress = m_currentReturnKeyPress;
	if (hasSelected)
	{
		return m_highlightIndex;
	}
	return -1;
}

