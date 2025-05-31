#pragma once
#include <SFML/Graphics.hpp>
#include "SFML_2DCamera.h"
class SFML_GameWorldLayer: public sf::Drawable
{
public:
	SFML_GameWorldLayer(std::string textureFile, float parallaxFactor, sf::Vector2f scrollSpeed, int viewPortWidth, int viewPortHeight);
	~SFML_GameWorldLayer();

	void followCamera(SFML_2DCamera* camera);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setParallaxFactor(float parallaxFactor);
	float getParallaxFactor();

	void setScrollSpeed(sf::Vector2f scrollSpeed);
	void update(float elapsedTime);


private:
	sf::Texture m_layerTexture;
	sf::VertexArray m_layerVertices;

	float m_parallaxFactor;

	sf::Vector2f m_offSet;
	sf::Vector2f m_scrollSpeed;


};

