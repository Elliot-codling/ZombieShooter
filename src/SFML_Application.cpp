#include "SFML_Application.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

bool direction = false;	//false is left, true is right
SFML_Application::SFML_Application(int windowWidth, int windowHeight, bool fullscreen):
m_window(sf::VideoMode(windowWidth, windowHeight), "Zombie Shooter Game", fullscreen ? sf::Style::Fullscreen : sf::Style::Default),
m_titleScreen("media/textures/title-screen.png", windowWidth, windowHeight),
m_mainMenu("media/menuInfo/main-menu.txt", windowWidth, windowHeight),
m_desiredUpdateTime(sf::seconds( 1.f/60.f)),
m_gameWorld(windowWidth, windowHeight, &m_window),
m_timeCounter(sf::seconds(0)),
m_FPSCounter(0),
m_creditMenu("media/menuInfo/credits.txt", windowWidth, windowHeight),
m_loreMenu("media/menuInfo/loreText.txt", windowWidth, windowHeight)
{
	

	//Only initialise if the font can be loaded
	m_initalised = m_textFont.loadFromFile("media/font/SegoeMarker.ttf");
	m_messageText.setFont(m_textFont);	//Set the message to the font
	m_screenWidth = windowWidth;
	m_screenHeight = windowHeight;
	m_windowState = TITLESCREEN;
	

	//m_window.setFramerateLimit(60);

	//Used for message that will move right to left
	m_messageText.setString("Main Menu Screen");
	m_messageText.setCharacterSize(20);
	
	sf::FloatRect textBox = m_messageText.getLocalBounds();
	m_messageText.setPosition(10, 10);

	//Main Menu
	m_mainMenu.setScale(0.85f, 0.85f);
	m_mainMenu.setPosition(m_screenWidth / 2, m_screenHeight / 2);

	
}
SFML_Application::~SFML_Application()
{
	
}


void SFML_Application::update(sf::Time elapsedTime)
{
	//Update events
	events();
	int selection;

	//New switch case statement
	switch (m_windowState)
	{
	case TITLESCREEN:
		if (anyKeyPressed)
		{
			m_windowState = MAINMENU;
			anyKeyPressed = false;
		}
		m_titleScreen.update(elapsedTime);
		break;
	case MAINMENU:
		selection = m_mainMenu.update(elapsedTime);
		if (selection >= 0)
		{
			if (selection == 0)
			{
				m_windowState = LOREMENU;
				m_loreMenu.reset();
				
				upKeyPressed = false;
			}
			else if (selection == 1)
			{
				m_windowState = CREDITSMENU;
				upKeyPressed = false;
			}
			else if (selection == 2)
			{
				m_windowState = EXITING;
				m_window.close();
				upKeyPressed = false;
			}
		}
		break;
	case CREDITSMENU:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			m_creditMenu.resetCredits();
			m_windowState = MAINMENU;
		}
		if (m_creditMenu.update(elapsedTime))
		{
			m_creditMenu.resetCredits();
			m_windowState = MAINMENU;
		}
		break;
	case LOREMENU:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			m_windowState = MAINMENU;
		}
		if (m_loreMenu.update(elapsedTime))
		{
			m_windowState = GAMEPLAYING;
			m_gameWorld.resetGame();
		}
		
		break;
	case GAMEPLAYING:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			m_windowState = MAINMENU;
		}

		if (m_gameWorld.update(elapsedTime.asSeconds()))
		{
			m_windowState = MAINMENU;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !fKeyPressed)
		{
			displayFPS = !displayFPS;
			fKeyPressed = true;
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F) && fKeyPressed)
		{
			fKeyPressed = false;
		}
		
		break;
	
	}
}

void SFML_Application::render()
{

	m_window.clear();
	switch (m_windowState)
	{
	case TITLESCREEN:
		m_window.draw(m_titleScreen);
		//m_window.draw(m_messageText);
		break;
	case MAINMENU:
		m_window.draw(m_mainMenu);
		break;
	case CREDITSMENU:
		m_window.draw(m_creditMenu);
		break;
	case LOREMENU:
		m_window.draw(m_loreMenu);
		break;
	case GAMEPLAYING:
		m_window.draw(m_gameWorld);
		if (displayFPS)
		{
			m_window.draw(m_messageText);
		}
		break;
	case EXITING:
		break;
	}
	m_window.display();
}

void SFML_Application::events()
{
	//Currently used, however next slide is accessed by arrow keys
	while (m_window.pollEvent(m_event))		//Grab new events
	{
		switch (m_event.type)
		{
		case sf::Event::Closed:
			m_window.close();		//Close if the close button is pressed.
			break;
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				upKeyPressed = true;
				downKeyPressed = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				upKeyPressed = false;
				downKeyPressed = true;
			}
			
			anyKeyPressed = true;
			
			break;
		case sf::Event::KeyReleased:
			anyKeyPressed = false;

		default:
			break;

		}
	}

}

void SFML_Application::updateFPS(sf::Time elapsedTime)
{
	m_timeCounter += elapsedTime;

	m_FPSCounter++;

	if (m_timeCounter >= sf::seconds(1.0f))
	{
		m_messageText.setString("Refresh rate = " + std::to_string(m_FPSCounter) +
			" fps \n" +
			"Time between screen refreshes \n= " +
			std::to_string(m_timeCounter.asMicroseconds() / m_FPSCounter) +
			" microseconds \n");

		m_timeCounter -= sf::seconds(1.0f);
		m_FPSCounter = 0;
	}
}



void SFML_Application::run()
{
	if (!m_initalised)
	{
		return;		//Exit if the window has not been initialised
	}
	sf::Clock clock;
	m_window.setKeyRepeatEnabled(false);

	//Var to track the time since update() was last executed
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (m_window.isOpen())
	{
		//Time since the last loop
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > m_desiredUpdateTime)
		{
			//Update application logic
			update(m_desiredUpdateTime);

			timeSinceLastUpdate -= m_desiredUpdateTime;
		}

		//Calculate FPS
		updateFPS(elapsedTime);

		//Update render
		render();
	}
}

