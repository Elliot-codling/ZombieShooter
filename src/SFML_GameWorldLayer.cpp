#include "SFML_GameWorldLayer.h"

#include <iostream>

SFML_GameWorldLayer::SFML_GameWorldLayer(std::string textureFile, float parallaxFactor, sf::Vector2f scrollSpeed, int viewPortWidth, int viewPortHeight):
m_layerTexture(),
m_layerVertices(sf::Quads, 4),
m_parallaxFactor(parallaxFactor)
{
	if (m_layerTexture.loadFromFile(textureFile))
	{
		//Texture will repeat
		m_layerTexture.setRepeated(true);

		//Set the vertices of the quad
		//0 --------- 1
		//|           |
		//|           |
		//|           |
		//3 --------- 2

		m_layerVertices[0].position = sf::Vector2f(0.f, 0.f);
		m_layerVertices[1].position = sf::Vector2f(0.f, viewPortHeight);
		m_layerVertices[2].position = sf::Vector2f(viewPortWidth, viewPortHeight);
		m_layerVertices[3].position = sf::Vector2f(viewPortWidth, 0.f);
		

	}
	setScrollSpeed(scrollSpeed);
}

SFML_GameWorldLayer::~SFML_GameWorldLayer()
{
	
}

void SFML_GameWorldLayer::followCamera(SFML_2DCamera* camera)
{
	//Find the visible area rect of the camera
	sf::FloatRect cameraWindow = camera->getCameraWindow(m_parallaxFactor);

	//calculate the left, right, top and bottom values
	int left = cameraWindow.left + m_offSet.x;
	int right = cameraWindow.left + cameraWindow.width + m_offSet.x;
	int top = cameraWindow.top + m_offSet.y;
	int bottom = cameraWindow.top + cameraWindow.height + m_offSet.y;

	//Set the texture coord using those values
	m_layerVertices[0].texCoords = sf::Vector2f(left, top);
	m_layerVertices[1].texCoords = sf::Vector2f(left, bottom);
	m_layerVertices[2].texCoords = sf::Vector2f(right, bottom);
	m_layerVertices[3].texCoords = sf::Vector2f(right, top);
}

void SFML_GameWorldLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Assign the m_layerTexture to the renderstate
	states.texture = &m_layerTexture;

	//Draw the quad with using renderstate
	target.draw(m_layerVertices, states);
}


void SFML_GameWorldLayer::setParallaxFactor(float parallaxFactor)
{
	m_parallaxFactor = parallaxFactor;
}

float SFML_GameWorldLayer::getParallaxFactor()
{
	return m_parallaxFactor;
}

void SFML_GameWorldLayer::setScrollSpeed(sf::Vector2f scrollSpeed)
{
	m_scrollSpeed = scrollSpeed;
}


void SFML_GameWorldLayer::update(float elapsedTime)
{
	m_offSet = m_offSet + elapsedTime * m_scrollSpeed;
}


