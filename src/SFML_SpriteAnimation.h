#pragma once
#include "SFML/Graphics.hpp"
class SFML_SpriteAnimation
{
public:
	SFML_SpriteAnimation();
	~SFML_SpriteAnimation();

	void setSpriteSheet(sf::Texture* spriteTexture);

	void addFrame(sf::IntRect textureRect, sf::Vector2f centre);
	bool getCurrentFrame(sf::IntRect* rect, sf::Vector2f* centre);
	void setFrameTime(float timePerFrame);
	float getTimePerFrame();

	sf::Texture* getSpriteSheet();
	int getNumberOfFrames();
	void getTextureInfo(int newFrame, sf::IntRect* rect, sf::Vector2f* centre);

	void setLoop(bool loop);
	bool isLooped() const;

	void setCanBeInterrupted(bool trueOrFalse);
	bool canBeInterrupted() const;

	void incrementFrameNum();
	int getCurrentFrameNum();
	void resetCurrentAnimation();

	bool isCompleted();


private:
	//Frame info
	std::vector<sf::IntRect> m_frameRectangleList;
	std::vector<sf::Vector2f> m_frameCentreList;

	//Pointer to texture obj
	sf::Texture* m_spriteSheet;

	//Current frame num and time delay
	int m_currentFrameNum;
	float m_timePerFrame;

	//Animation control
	bool m_isLoop;
	bool m_canBeInterruped;

};

