#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class SFML_TitleScreen: public Drawable
{
public:
	SFML_TitleScreen(string textureFile, int windowWidth, int windowHeight);
	~SFML_TitleScreen();

	void update(Time elapsedTime);

private:
	virtual void draw(RenderTarget& target, RenderStates states) const;

	Texture m_titleScreenTexture;
	Sprite m_titleScreenSprite;

	Texture m_messageTexture;
	Sprite m_messageSprite;

	Time m_flashingTime;
	Time m_timeSinceLastFlash;
	bool m_flashEnable;

};

