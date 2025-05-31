#include "SFML_SpriteObject.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

SFML_SpriteObject::SFML_SpriteObject():
m_initialised(false)
{
	m_defaultTexture = NULL;
}

SFML_SpriteObject::~SFML_SpriteObject()
{
	if (m_defaultTexture != NULL)
	{
		delete m_defaultTexture;
	}
}

bool SFML_SpriteObject::setDefaultTexture(std::string textureFile)
{
	if (m_defaultTexture != NULL)
	{
		delete m_defaultTexture;
	}
	m_defaultTexture = new sf::Texture();

	if (!m_defaultTexture->loadFromFile(textureFile))
	{
		m_initialised = false;
		delete m_defaultTexture;
		m_defaultTexture = NULL;
		return false;
	}
	m_spriteTexture = m_defaultTexture;

	m_spriteOrigin = sf::Vector2f(m_defaultTexture->getSize().x / 2, m_defaultTexture->getSize().y / 2);
	m_textureRectangle = sf::IntRect(0, 0, m_defaultTexture->getSize().x, m_defaultTexture->getSize().y);

	m_initialised = true;
	return true;
}

bool SFML_SpriteObject::setDefaultTexture(std::string textureFile, std::string spriteInfoFile)
{
	if (m_defaultTexture != NULL)
	{
		delete m_defaultTexture;
	}
	m_defaultTexture = new sf::Texture();

	if (!m_defaultTexture->loadFromFile(textureFile))
	{
		m_initialised = false;
		delete m_defaultTexture;
		m_defaultTexture = NULL;
		return false;
	}

	m_spriteTexture = m_defaultTexture;

	std::string s_left, s_top, s_width, s_height, s_xcenter, s_ycenter;
	int i_left, i_top, i_width, i_height, i_xcenter, i_ycenter;

	std::ifstream inputFile(spriteInfoFile);

	if (inputFile.is_open())
	{
		std::string stringLine;
		std::getline(inputFile, stringLine);

		std::istringstream stringStream(stringLine);
		stringStream >> s_left;
		stringStream >> s_top;
		stringStream >> s_width;
		stringStream >> s_height;
		stringStream >> s_xcenter;
		stringStream >> s_ycenter;

		//Convert to int
		i_left = std::stoi(s_left);
		i_top = std::stoi(s_top);
		i_width = std::stoi(s_width);
		i_height = std::stoi(s_height);
		i_xcenter = std::stoi(s_xcenter);
		i_ycenter = std::stoi(s_ycenter);

		//Set sprite origin and texture rect
		m_spriteOrigin = sf::Vector2f(i_xcenter - i_left, i_ycenter - i_top);
		m_textureRectangle = sf::IntRect(i_left, i_top, i_width, i_height);

		inputFile.close();

		m_initialised = true;
		return true;
	}
	return false;
}

void SFML_SpriteObject::setColor(const sf::Color& color)
{
	m_sprite.setColor(color);
}

sf::Vector2f SFML_SpriteObject::getWorldPos()
{
	return getTransform().transformPoint(0, 0);
}

sf::Vector2f SFML_SpriteObject::getScreenPos(sf::Transform cameraScreenTransform)
{
	sf::Transform worldViewProjTransform = cameraScreenTransform * getTransform();
	return worldViewProjTransform * sf::Vector2f();
}

sf::FloatRect SFML_SpriteObject::getLocalBounds() const
{
	float left = static_cast<float>(-m_spriteOrigin.x);
	float top = static_cast<float>(-m_spriteOrigin.y);
	float width = static_cast<float>(m_textureRectangle.width);
	float height = static_cast<float>(m_textureRectangle.height);

	return sf::FloatRect(left, top, width, height);
}

sf::FloatRect SFML_SpriteObject::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

void SFML_SpriteObject::update(float elapsedTime)
{
	if (!m_initialised)
	{
		return;
	}

	//Set sprite texture, rect and origin
	if (m_spriteTexture != NULL)
	{
		m_sprite.setTexture(*m_spriteTexture);
	}

	m_sprite.setTextureRect(m_textureRectangle);

	m_sprite.setOrigin(m_spriteOrigin);

}

void SFML_SpriteObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
}
