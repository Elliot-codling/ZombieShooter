#include "SFML_GameWorld.h"
#include <fstream>
#include <iostream>


SFML_GameWorld::SFML_GameWorld(int windowWidth, int windowHeight, sf::RenderWindow* parentWindow):
m_windowWidth(windowWidth),
m_windowHeight(windowWidth),
m_camera(windowWidth, windowHeight)
{
	//Create gameworld layer object using wall.png
	SFML_GameWorldLayer* background = new SFML_GameWorldLayer("media/textures/wall.png", 1.0f, {0.f, 0.f}, windowWidth, windowHeight);
	m_gameWorldLayerList.push_back(background);		//Add to list
	SFML_GameWorldLayer* fog = new SFML_GameWorldLayer("media/textures/fog.png", 0.8f, { 100.f, 100.f }, windowWidth, windowHeight);
	m_gameWorldLayerList.push_back(fog);

	SFML_SpriteObject* night = new SFML_SpriteObject();
	night->setDefaultTexture("media/textures/night.png", "media/spriteInfo/night.txt");
	night->setColor(sf::Color(255, 255, 255, 0));
	m_spriteObjects.push_back(night);

	std::ifstream inputFile("media/spriteInfo/health.txt");
	if (inputFile.is_open())
	{
		std::string stringLine;
		std::getline(inputFile, stringLine);

		m_healthFont.loadFromFile(stringLine);			//Set health font
	}
	


	//Camera
	m_camera.setPosition(sf::Vector2f(0, 0));

	//parent window
	m_parentWindow = parentWindow;

	//Init zombies
	srand(time(NULL));
	m_numberOfZombies = 10;

	for (int i = 0; i < m_numberOfZombies; i++)
	{
		SFML_NPCSpriteObject* npcSprite = new SFML_NPCSpriteObject();
		npcSprite->setIdleAnimation("media/textures/zombie-idle.png", "media/spriteInfo/zombie-idle.txt", 1.0f);
		npcSprite->setWalkingAnimation("media/textures/zombie-move.png", "media/spriteInfo/zombie-move.txt", 1.0f);
		npcSprite->setAttackingAnimation("media/textures/zombie-attack.png", "media/spriteInfo/zombie-attack.txt", 1.0f);

		npcSprite->setPosition(rand() % 4000 - 2000, rand() % 4000 - 2000);
		npcSprite->setTargetLocation(sf::Vector2f(rand() % 4000 - 2000, rand() % 4000 - 2000));
		m_zombieCharacterList.push_back(npcSprite);
	}

	//Soldier
	m_playerCharacter = new SFML_PlayableSpriteObject();
	//Flashlight
	m_playerCharacter->setFlashlightIdleAnimation("media/textures/hero_flashlight_idle.png", "media/spriteInfo/hero_flashlight_idle.txt", 1.0f);
	m_playerCharacter->setFlashlightWalkingAnimation("media/textures/hero_flashlight_move.png", "media/spriteInfo/hero_flashlight_move.txt", 1.0f);
	m_playerCharacter->setFlashlightMeleeAnimation("media/textures/hero_flashlight_melee.png", "media/spriteInfo/hero_flashlight_melee.txt", 1.0f);
	//Knife
	m_playerCharacter->setKnifeIdleAnimation("media/textures/hero_knife_idle.png", "media/spriteInfo/hero_knife_idle.txt", 1.0f);
	m_playerCharacter->setKnifeWalkingAnimation("media/textures/hero_knife_idle.png", "media/spriteInfo/hero_knife_idle.txt", 1.0f);
	m_playerCharacter->setKnifeMeleeAnimation("media/textures/hero_knife_idle.png", "media/spriteInfo/hero_knife_idle.txt", 1.0f);
	//Pistol
	m_playerCharacter->setPistolIdleAnimation("media/textures/hero_pistol_idle.png", "media/spriteInfo/hero_pistol_idle.txt", 1.0f);
	m_playerCharacter->setPistolWalkingAnimation("media/textures/hero_pistol_move.png", "media/spriteInfo/hero_pistol_move.txt", 1.0f);
	m_playerCharacter->setPistolMeleeAnimation("media/textures/hero_pistol_melee.png", "media/spriteInfo/hero_pistol_melee.txt", 1.0f);
	m_playerCharacter->setPistolShootAnimation("media/textures/hero_pistol_shoot.png", "media/spriteInfo/hero_pistol_shoot.txt", 1.0f);

	//Rifle
	m_playerCharacter->setRifleIdleAnimation("media/textures/hero_rifle_idle.png", "media/spriteInfo/hero_rifle_idle.txt", 1.0f);
	m_playerCharacter->setRifleWalkingAnimation("media/textures/hero_rifle_move.png", "media/spriteInfo/hero_rifle_move.txt", 1.0f);
	m_playerCharacter->setRifleMeleeAnimation("media/textures/hero_rifle_melee.png", "media/spriteInfo/hero_rifle_melee.txt", 1.0f);
	m_playerCharacter->setRifleShootAnimation("media/textures/hero_rifle_shoot.png", "media/spriteInfo/hero_rifle_shoot.txt", 1.0f);


	m_playerCharacter->equipFlashlight();
	m_playerCharacter->setWeaponDmg(2);
	m_playerCharacter->toIdleState();

	m_playerCharacter->setPosition(0, 300);

	SFML_GameWorldLayer* foreground = new SFML_GameWorldLayer("media/textures/wire.png", 0.3f, { 0.f, 0.f }, windowWidth, windowHeight);
	m_gameWorldLayerList.push_back(foreground);
	std::sort(m_gameWorldLayerList.begin(), m_gameWorldLayerList.end(), layerSortFunction);

	m_healthText.setString("Health: " + std::to_string(m_playerCharacter->getHealth()) + "%");
	m_healthText.setPosition(10, 1000);
	m_healthText.setFont(m_healthFont);
	m_healthText.setCharacterSize(50);
	m_healthText.setFillColor(sf::Color::White);
}


SFML_GameWorld::~SFML_GameWorld()
{
	//Clear gameworldlayer list
	for (std::vector<SFML_GameWorldLayer*>::iterator index = m_gameWorldLayerList.begin(); index != m_gameWorldLayerList.end(); index++)
	{
		delete(*index);
	}

	m_gameWorldLayerList.clear();

	//delete m_animatedObject;
}

void SFML_GameWorld::processEvents(float elapsedTime)
{
	//Camera zoom
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && m_camera.getZoomLevel() <= 3.0f)
	{
		m_camera.zoomDown(elapsedTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && m_camera.getZoomLevel() >= 0.8f)
	{
		m_camera.zoomUp(elapsedTime);
	}

	sf::Transform transform;
	transform = m_camera.getProjTransform() * m_camera.getViewTransform();

	//Take inverse
	sf::Transform inv = transform.getInverse();

	//get mouse pos
	sf::Vector2f mouseScreenPosition = sf::Vector2f(sf::Mouse::getPosition(*m_parentWindow));

	//sf::Vector2f wp = inv.transformPoint(m_playerCharacter->getPosition());
	sf::Vector2f playerPosition = m_playerCharacter->getPosition();
	sf::FloatRect playerBox = m_playerCharacter->getGlobalBounds();

	SFML_BulletSpriteObject* bullet = m_playerCharacter->processEvents(elapsedTime, transform, mouseScreenPosition);
	if (bullet)
	{
		m_bulletList.push_back(bullet);
	}

	bool playerHit = false;
	//NPC character to collide with bullets
	for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++)
	{
		sf::FloatRect boundingBox = m_zombieCharacterList[counter]->getGlobalBounds();
		for (unsigned int counterTwo = 0; counterTwo < m_bulletList.size(); counterTwo++)
		{
			if (boundingBox.contains(m_bulletList[counterTwo]->getPosition()))
			{
				//Zombie collision detection - bullet
				m_zombieCharacterList[counter]->reduceHealth(m_playerCharacter->getWeaponDmg());
				m_zombieCharacterList[counter]->setTargetLocation(playerPosition);			//Go to player
			}
		}

		if (boundingBox.intersects(playerBox) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_zombieCharacterList[counter]->reduceHealth(2);
		}
		
		if (playerBox.intersects(boundingBox) && m_zombieCharacterList[counter]->getAliveOrDead())
		{
			playerHit = true;				//Zombie collision detection - player

			//Change zombie animation
			m_zombieCharacterList[counter]->toAttackingState();
		}
		else 
		{
			if (m_zombieCharacterList[counter]->isInVision(playerPosition) && m_zombieCharacterList[counter]->getAliveOrDead())
			{
				//Move zombies towards the player and change animation to walking
				m_zombieCharacterList[counter]->setTargetLocation(playerPosition);			//Follow player
				m_zombieCharacterList[counter]->toWalkingState();

			}
			else
			{
				//Else zombie isnt moving so set to idle
				m_zombieCharacterList[counter]->toIdleState();
			}
		}

		//Hide zombie if below 0 hp
		if (m_zombieCharacterList[counter]->getHealth() <= 0)
		{
			m_zombieCharacterList[counter]->setIsAlive(false);
		}
	}

	//Player hit!
	if (playerHit)
	{
		if (rand() % 5 == 0)
		{
			m_playerCharacter->reduceHealth(2);			//Apply damage to player
			m_healthText.setString("Health: " + std::to_string(m_playerCharacter->getHealth()) + "%");
		}	
		
	}
	
	
	//Select weapons
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_playerCharacter->equipFlashlight();
		m_playerCharacter->setWeaponDmg(2);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_playerCharacter->equipKnife();
		m_playerCharacter->setWeaponDmg(5);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		m_playerCharacter->equipPistol();
		m_playerCharacter->setWeaponDmg(10);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		m_playerCharacter->equipRifle();
		m_playerCharacter->setWeaponDmg(12);
	}

}

bool SFML_GameWorld::update(float elapsedTime)
{
	processEvents(elapsedTime);


	//Day night cycle
	//Current time till dark -> 30 secs
	//Time till day from dark -> 30 secs
	m_spriteObjects[0]->update(elapsedTime);
	if (currentTime >= cycleTimeSeconds || currentTime < 0)
	{
		isDay = !isDay;
	}

	if (isDay)
	{
		currentTime += elapsedTime;
		float brightnessPercent = (currentTime / cycleTimeSeconds);
		m_spriteObjects[0]->setColor(sf::Color(255, 255, 255, 200 * brightnessPercent));
	}
	else
	{
		currentTime -= elapsedTime;
		float brightnessPercent = (abs(currentTime) / cycleTimeSeconds);
		m_spriteObjects[0]->setColor(sf::Color(255, 255, 255, 200 * brightnessPercent));
	}

	for (int counter = 0; counter < m_gameWorldLayerList.size(); counter++)
	{
		m_gameWorldLayerList[counter]->update(elapsedTime);
		m_gameWorldLayerList[counter]->followCamera(&m_camera);
	}

	//Animation
	m_playerCharacter->update(elapsedTime);
	m_camera.setPosition(m_playerCharacter->getWorldPos());

	for (unsigned int counter = 0; counter < m_bulletList.size(); counter++)
	{
		m_bulletList[counter]->update(elapsedTime);
	}

	//Update zombies
	for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++)
	{
		m_zombieCharacterList[counter]->update(elapsedTime);
	}

	if (m_playerCharacter->getHealth() <= 0)
	{
		return true;
	}

	return false;
	
}


void SFML_GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (unsigned int counter = 0; counter < m_gameWorldLayerList.size(); counter++)
	{
		if (m_gameWorldLayerList[counter]->getParallaxFactor() >= 1.0f)
		{
			target.draw(*m_gameWorldLayerList[counter]);		//Draw each layer
		}
		
	}

	sf::RenderStates renderState;
	renderState.transform = m_camera.getProjTransform() * m_camera.getViewTransform();

	//target.draw(m_spriteObject, renderState);
	//Draw zombies
	for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++)
	{
		if (m_zombieCharacterList[counter]->getAliveOrDead())
		{
			//sf::Vector2f position = m_zombieCharacterList[counter]->getPosition();
			target.draw(*m_zombieCharacterList[counter], renderState);
		}
		
	}

	//hero
	target.draw(*m_playerCharacter, renderState);

	for (unsigned int counter = 0; counter < m_bulletList.size(); counter++)
	{
		target.draw(*m_bulletList[counter], renderState);
	}

	for (unsigned int counter = 0; counter < m_gameWorldLayerList.size(); counter++)
	{
		if (m_gameWorldLayerList[counter]->getParallaxFactor() < 1.0f)
		{
			target.draw(*m_gameWorldLayerList[counter]);		//Draw each layer
		}

	}

	target.draw(*m_spriteObjects[0]);
	target.draw(m_healthText);
	
}

bool SFML_GameWorld::layerSortFunction(SFML_GameWorldLayer* a, SFML_GameWorldLayer* b)
{
	return (a->getParallaxFactor() > b->getParallaxFactor());
}

void SFML_GameWorld::resetGame()
{
	m_zombieCharacterList.clear();
	for (int i = 0; i < m_numberOfZombies; i++)
	{
		SFML_NPCSpriteObject* npcSprite = new SFML_NPCSpriteObject();
		npcSprite->setIdleAnimation("media/textures/zombie-idle.png", "media/spriteInfo/zombie-idle.txt", 1.0f);
		npcSprite->setWalkingAnimation("media/textures/zombie-move.png", "media/spriteInfo/zombie-move.txt", 1.0f);
		npcSprite->setAttackingAnimation("media/textures/zombie-attack.png", "media/spriteInfo/zombie-attack.txt", 1.0f);

		npcSprite->setPosition(rand() % 4000 - 2000, rand() % 4000 - 2000);
		npcSprite->setTargetLocation(sf::Vector2f(rand() % 4000 - 2000, rand() % 4000 - 2000));
		m_zombieCharacterList.push_back(npcSprite);
	}

	m_playerCharacter->resetHealth();
	m_healthText.setString("Health: " + std::to_string(m_playerCharacter->getHealth()) + "%");
}
