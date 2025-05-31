#pragma once
#include "SFML_SpriteObject.h"
#include "SFML_SpriteAnimation.h"
class SFML_AnimatedSpriteObject : public SFML_SpriteObject
{
public:
	SFML_AnimatedSpriteObject();
	virtual ~SFML_AnimatedSpriteObject();

	int addAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);

	//Set current animation
	void setCurrentAnimation(int animationIndex);

	//Return address of current animation
	SFML_SpriteAnimation* getCurrentAnimation();

	virtual void update(float elapsedTime);

	//Control playback
	void play();
	void pause();
	void stop();

private:
	std::vector<sf::Texture*> m_spriteTextureList;
	int m_currentAnimationID;
	float m_currentTime;
	bool m_isPaused;

protected:
	std::vector<SFML_SpriteAnimation*> m_animatedSpriteList;
	SFML_SpriteAnimation* m_currentAnimation;
};

