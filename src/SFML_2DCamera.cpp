#include "SFML_2DCamera.h"

SFML_2DCamera::SFML_2DCamera(int projectionWidth, int projectionHeight) :
	m_cameraPosition(0, 0),
	m_cameraWindowSize(projectionWidth, projectionHeight),
	m_cameraZoom(1)
{
	
}

SFML_2DCamera::~SFML_2DCamera()
{
	
}

void SFML_2DCamera::setPosition(sf::Vector2f target)
{
	m_cameraPosition = target;
}

void SFML_2DCamera::zoomUp(float elapsedTime)
{
	float zoomSpeed = 60.f;
	float zoomChange = m_cameraZoom * 0.1f * elapsedTime * zoomSpeed;
	m_cameraZoom = m_cameraZoom - zoomChange;
}

void SFML_2DCamera::zoomDown(float elapsedTime)
{
	float zoomSpeed = 60.f;
	float zoomChange = m_cameraZoom * 0.1f * elapsedTime * zoomSpeed;
	m_cameraZoom = m_cameraZoom + zoomChange;
}

sf::Transform SFML_2DCamera::getViewTransform() const
{
	//Transform the coordinate from WORLD space to CAMERA space
	//Center at the middle of the window

	sf::Transform transform = sf::Transform::Identity;
	transform.translate(m_cameraPosition);
	return transform.getInverse();
}

sf::Transform SFML_2DCamera::getProjTransform() const
{
	//Transform the coordinate from CAMERA space to WORLD(SCREEN) space
	//WORLD space origin is the top left
	sf::Transform transform = sf::Transform::Identity;
	transform.translate(m_cameraWindowSize.x / 2, m_cameraWindowSize.y / 2);
	transform.scale(1.0f / m_cameraZoom, 1.0f / m_cameraZoom);
	return transform;
}

sf::FloatRect SFML_2DCamera::getCameraWindow(float parallaxFactor)
{
	sf::FloatRect window;

	window.left = m_cameraPosition.x - m_cameraWindowSize.x / 2 * m_cameraZoom * parallaxFactor;
	window.top = m_cameraPosition.y - m_cameraWindowSize.y / 2 * m_cameraZoom * parallaxFactor;

	window.width = m_cameraWindowSize.x * m_cameraZoom * parallaxFactor;
	window.height = m_cameraWindowSize.y * m_cameraZoom * parallaxFactor;

	return window;
}

