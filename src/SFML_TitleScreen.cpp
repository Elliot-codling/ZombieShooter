#include "SFML_TitleScreen.h"
#include <iostream>
SFML_TitleScreen::SFML_TitleScreen(string textureFile, int windowWidth, int windowHeight)
{
	//Background Texture
	m_titleScreenTexture.loadFromFile(textureFile);
	m_titleScreenSprite.setTexture(m_titleScreenTexture);
	m_titleScreenSprite.setScale(windowWidth / static_cast<float>(1920), windowHeight / static_cast<float>(1080));

	Vector2u bkTextureSize = m_titleScreenTexture.getSize();
	m_titleScreenSprite.setTextureRect(IntRect(0, 0, bkTextureSize.x, bkTextureSize.y));

	m_titleScreenSprite.setPosition(0, 0);
	

	//Message
	m_messageTexture.loadFromFile("media/textures/continue.png");
	m_messageSprite.setTexture(m_messageTexture);

	m_messageSprite.setPosition(windowWidth * 0.5f, windowHeight * 0.75f);
	Vector2u msgTextureSize = m_messageTexture.getSize();
	m_messageSprite.setOrigin(msgTextureSize.x / 2, msgTextureSize.y / 2);
	m_messageSprite.setTextureRect(IntRect(0, 0, msgTextureSize.x, msgTextureSize.y));

	m_messageSprite.setColor(Color(255, 0, 0));

	//Flash
	m_timeSinceLastFlash = Time::Zero;
	m_flashingTime = seconds(0.2f);


}


SFML_TitleScreen::~SFML_TitleScreen()
{
	
}

void SFML_TitleScreen::update(Time elapsedTime)
{
	m_timeSinceLastFlash += elapsedTime;

	if (m_timeSinceLastFlash > m_flashingTime)
	{
		m_flashEnable = !m_flashEnable;
		m_timeSinceLastFlash -= m_flashingTime;
		if (m_flashEnable)
		{
			m_messageSprite.setColor(Color(255, 255, 255));
		}
		else
		{
			m_messageSprite.setColor(Color(255, 0, 0));
		}
	}
}

void SFML_TitleScreen::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_titleScreenSprite);
	target.draw(m_messageSprite);
}


