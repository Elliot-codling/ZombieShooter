#pragma once
#include <SFML/Graphics.hpp>
class SFML_2DCamera
{
public: 
	SFML_2DCamera(int projectionWidth, int projectionHeight);
	~SFML_2DCamera();

	sf::FloatRect getCameraWindow(float parallaxFactor);
	void setPosition(sf::Vector2f target);
	void zoomUp(float elapsedTime);
	void zoomDown(float elapsedTime);

	sf::Transform getViewTransform() const;
	sf::Transform getProjTransform() const;

	float getZoomLevel() { return m_cameraZoom; }

private:
	sf::Vector2f m_cameraPosition;
	sf::Vector2f m_cameraWindowSize;

	float m_cameraZoom;
	
};

