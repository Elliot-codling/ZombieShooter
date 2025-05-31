#include "SFML_SpriteAnimation.h"

SFML_SpriteAnimation::SFML_SpriteAnimation():
m_currentFrameNum(0),
m_canBeInterruped(true),
m_isLoop(true)
{
	
}

SFML_SpriteAnimation::~SFML_SpriteAnimation()
{
	m_frameCentreList.clear();
	m_frameRectangleList.clear();
}

void SFML_SpriteAnimation::setSpriteSheet(sf::Texture* spriteTexture)
{
	m_spriteSheet = spriteTexture;
}

sf::Texture* SFML_SpriteAnimation::getSpriteSheet()
{
	return m_spriteSheet;
}

void SFML_SpriteAnimation::addFrame(sf::IntRect textureRect, sf::Vector2f centre)
{
	m_frameRectangleList.push_back(textureRect);
	m_frameCentreList.push_back(centre);
}

int SFML_SpriteAnimation::getNumberOfFrames()
{
	return m_frameRectangleList.size();
}

bool SFML_SpriteAnimation::getCurrentFrame(sf::IntRect* rect, sf::Vector2f* centre)
{
	if ((m_currentFrameNum < 0) || (m_currentFrameNum >= m_frameRectangleList.size()))
	{
		//Out of bounds position is supplied
		return false;
	}
	//Retrieve the rect and centre data
	sf::IntRect iRect = m_frameRectangleList[m_currentFrameNum];
	sf::Vector2f iCenter = m_frameCentreList[m_currentFrameNum];

	//Copy info over
	rect->left = iRect.left;
	rect->top = iRect.top;
	rect->width = iRect.width;
	rect->height = iRect.height;

	centre->x = iCenter.x;
	centre->y = iCenter.y;

	return true;
}

int SFML_SpriteAnimation::getCurrentFrameNum()
{
	return m_currentFrameNum;
}

void SFML_SpriteAnimation::resetCurrentAnimation()
{
	m_currentFrameNum = 0;
}

void SFML_SpriteAnimation::setFrameTime(float timePerFrame)
{
	m_timePerFrame = timePerFrame;
}

float SFML_SpriteAnimation::getTimePerFrame()
{
	return m_timePerFrame;
}


void SFML_SpriteAnimation::incrementFrameNum()
{
	m_currentFrameNum++;
	if (m_currentFrameNum > m_frameRectangleList.size() - 1)
	{
		if (m_isLoop)
		{
			resetCurrentAnimation();
		}
		else
		{
			m_currentFrameNum = m_frameRectangleList.size() - 1;
		}
	}
}

bool SFML_SpriteAnimation::isCompleted()
{
	if (m_currentFrameNum >= m_frameRectangleList.size() - 1)
	{
		return true;
	}
	return false;
}

bool SFML_SpriteAnimation::isLooped() const
{
	return m_isLoop;
}

void SFML_SpriteAnimation::setLoop(bool loop)
{
	m_isLoop = loop;
}

bool SFML_SpriteAnimation::canBeInterrupted() const
{
	return m_canBeInterruped;
}

void SFML_SpriteAnimation::setCanBeInterrupted(bool trueOrFalse)
{
	m_canBeInterruped = trueOrFalse;
}

