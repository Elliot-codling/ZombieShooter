#pragma once
#include <SFML/Graphics.hpp>
#include "SFML_TitleScreen.h"
#include "SFML_GameMenu.h"
#include "SFML_GameWorld.h"
#include "SFML_GameWorldLayer.h"
#include "SFML_Credits.h"
#include "SFML_LoreScreen.h"

class SFML_Application : public sf::NonCopyable
{
public:
	SFML_Application(int windowWidth, int windowHeight, bool fullscreen);
	~SFML_Application();

	void run();
private:
	void update(sf::Time elapsedTime);
	void render();
	void events();

	void updateFPS(sf::Time elapsedTime);

	bool m_initalised;
	bool upKeyPressed;
	bool downKeyPressed;
	bool anyKeyPressed = false;

	sf::RenderWindow m_window;
	
	std::size_t m_screenWidth;
	std::size_t m_screenHeight;

	sf::Event m_event;
	sf::Font m_textFont;
	sf::Text m_messageText;

	enum windowState
	{
		TITLESCREEN,
		MAINMENU,
		GAMEPLAYING,
		EXITING,
		CREDITSMENU,
		LOREMENU
	};
	windowState m_windowState;

	SFML_TitleScreen m_titleScreen;
	SFML_GameMenu m_mainMenu;

	SFML_GameWorld m_gameWorld;

	sf::Time m_timeCounter;
	sf::Time m_desiredUpdateTime;
	std::size_t m_FPSCounter;

	//Credits and lore
	SFML_Credits m_creditMenu;
	SFML_LoreScreen m_loreMenu;

	//Display fps
	bool displayFPS = false;
	bool fKeyPressed = false;
	
};

