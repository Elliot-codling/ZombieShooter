#include "SFML_AnimatedSpriteObject.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
SFML_AnimatedSpriteObject::SFML_AnimatedSpriteObject():
m_currentAnimation(NULL),
m_isPaused(false),
m_currentAnimationID(-1)
{
		
}

SFML_AnimatedSpriteObject::~SFML_AnimatedSpriteObject()
{
	//Delete animation object in list
	for (std::vector<sf::Texture*>::iterator index = m_spriteTextureList.begin(); index != m_spriteTextureList.end(); index++)
	{
		delete* index;
	}

	m_spriteTextureList.clear();

	//Delete animation objects
	for (std::vector<SFML_SpriteAnimation*>::iterator index = m_animatedSpriteList.begin(); index != m_animatedSpriteList.end(); index++)
	{
		delete* index;
	}
	m_animatedSpriteList.clear();
}

int SFML_AnimatedSpriteObject::addAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	sf::Texture* spriteTexture = new sf::Texture();

	//Load the texture file
	if (!spriteTexture->loadFromFile(spriteSheetFilename))
	{
		return -1;
	}

	//Store the texture to list
	m_spriteTextureList.push_back(spriteTexture);

	//Create new animation
	SFML_SpriteAnimation* animation = new SFML_SpriteAnimation();
	//Store the address of the texture object in the animation
	animation->setSpriteSheet(spriteTexture);

	//Load sequences of frames
	//By reading spriteInfo file
	std::string left;
	std::string top;
	std::string width;
	std::string height;
	std::string xCenter;
	std::string yCenter;

	int iLeft, iTop, iWidth, iHeight, iXCenter, iYCenter;
	int frameCounter = 0;

	std::ifstream inputFile(spriteInfoFilename);

	if (inputFile.is_open())
	{
		do
		{
			std::string stringLine;
			std::getline(inputFile, stringLine);
			if (inputFile.good())
			{
				std::istringstream stringStream(stringLine);
				
				stringStream >> left;
				stringStream >> top;
				stringStream >> width;
				stringStream >> height;
				stringStream >> xCenter;
				stringStream >> yCenter;

				//Convert to ints
				iLeft = std::stoi(left);
				iTop = std::stoi(top);
				iWidth = std::stoi(width);
				iHeight = std::stoi(height);
				iXCenter = std::stoi(xCenter);
				iYCenter = std::stoi(yCenter);

				animation->addFrame(sf::IntRect(iLeft, iTop, iWidth, iHeight), sf::Vector2f(iXCenter - iLeft, iYCenter - iTop));
				frameCounter++;
			}
			else
			{
				break;
			}
		} while (true);
			
	}
	inputFile.close();

	if (frameCounter > 0)
	{
		animation->setFrameTime(animationTime / frameCounter);
		m_animatedSpriteList.push_back(animation);
		m_initialised = true;
		return m_animatedSpriteList.size() - 1;
	}
	return -1;
}

void SFML_AnimatedSpriteObject::setCurrentAnimation(int animationIndex)
{
	SFML_SpriteAnimation* newAnimation = m_animatedSpriteList[animationIndex];

	if (newAnimation)
	{
		if (m_currentAnimation != newAnimation)
		{
			m_currentAnimation = newAnimation;
			m_spriteTexture = m_currentAnimation->getSpriteSheet();
			m_currentAnimation->resetCurrentAnimation();
			m_currentAnimation->getCurrentFrame(&m_textureRectangle, &m_spriteOrigin);
			m_currentTime = 0;
		}
	}
}

SFML_SpriteAnimation* SFML_AnimatedSpriteObject::getCurrentAnimation()
{
	return m_currentAnimation;
}

void SFML_AnimatedSpriteObject::play()
{
	m_isPaused = false;
}

void SFML_AnimatedSpriteObject::pause()
{
	m_isPaused = true;
}

void SFML_AnimatedSpriteObject::stop()
{
	m_isPaused = true;
	m_currentTime = 0;
}

void SFML_AnimatedSpriteObject::update(float elapsedTime)
{
	if (!m_isPaused && m_currentAnimation)
	{
		float frameTime = m_currentAnimation->getTimePerFrame();

		//add elapsed time
		m_currentTime += elapsedTime;

		//If the current time is bigger than the frame time advance one frame
		if (m_currentTime >= frameTime)
		{
			m_currentAnimation->incrementFrameNum();
			m_currentAnimation->getCurrentFrame(&m_textureRectangle, &m_spriteOrigin);
			m_currentTime = m_currentTime - frameTime;
		}
	}
	SFML_SpriteObject::update(elapsedTime);
}






