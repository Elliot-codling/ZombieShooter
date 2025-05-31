#pragma once
#include <SFML/Graphics.hpp>
#include "SFML_GameWorldLayer.h"
#include "SFML_SpriteObject.h"
#include "SFML_AnimatedSpriteObject.h"

#include "SFML_NPCSpriteObject.h"
#include "SFML_PlayableSpriteObject.h"
#include "SFML_BulletSpriteObject.h"

class SFML_GameWorld : public sf::Drawable
{
public:
	SFML_GameWorld(int windowWidth, int windowHeight, sf::RenderWindow* parentWindow);
	~SFML_GameWorld();

	bool update(float elapsedTime);
	void resetGame();
private:
	void processEvents(float elapsedTime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	static bool layerSortFunction(SFML_GameWorldLayer* a, SFML_GameWorldLayer* b);
	

	int m_windowWidth;
	int m_windowHeight;

	std::vector<SFML_GameWorldLayer*> m_gameWorldLayerList;

	SFML_2DCamera m_camera;
	sf::Vector2f m_cameraPosiiton;

	sf::RenderWindow* m_parentWindow;

	//Animation
	SFML_AnimatedSpriteObject* m_animatedObject;
	int m_idleAnimationID;

	//Zombie list
	std::vector<SFML_NPCSpriteObject*> m_zombieCharacterList;
	int m_numberOfZombies;

	//Player
	SFML_PlayableSpriteObject* m_playerCharacter;

	std::vector<SFML_BulletSpriteObject*> m_bulletList;

	//Night
	SFML_SpriteObject* night;
	std::vector<SFML_SpriteObject*> m_spriteObjects;
	float cycleTimeSeconds = 30;
	float currentTime = 0;
	bool isDay = true;


	//Hud for health
	sf::Font m_healthFont;
	sf::Text m_healthText;
};

