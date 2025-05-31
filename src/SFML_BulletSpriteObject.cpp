#include "SFML_BulletSpriteObject.h"


SFML_BulletSpriteObject::SFML_BulletSpriteObject()
	: m_distanceTravelled(0)
	, m_active(true)
{
}


SFML_BulletSpriteObject::~SFML_BulletSpriteObject()
{
}

void SFML_BulletSpriteObject::setSpeed(float speed)
{
	m_moveSpeed = speed;
}

void SFML_BulletSpriteObject::setMoveDirection(sf::Vector2f directionVector, bool rotate)
{
	m_moveDirection = directionVector;

	if (rotate)
	{
		const float PI = 3.1415;
		float angleRadian = atan2(directionVector.y, directionVector.x);
		float angleDegree = angleRadian / PI * 180;
		setRotation(angleDegree);
	}
}

void SFML_BulletSpriteObject::setMaxRange(float range)
{
	m_maxRange = range;
}

void SFML_BulletSpriteObject::update(float elapsedTime)
{
	if (m_active)
	{
		move(m_moveDirection*m_moveSpeed*elapsedTime);
		m_distanceTravelled += m_moveSpeed*elapsedTime;

		if (m_distanceTravelled >= m_maxRange)
			m_active = false;
	}

	SFML_SpriteObject::update(elapsedTime);
}

bool SFML_BulletSpriteObject::isActive()
{
	return m_active;
}

void SFML_BulletSpriteObject::applyTexture(sf::Texture* texture)
{
	m_initialised = true;
	m_spriteTexture = texture;
	// Setting default origin and rectangle
	m_spriteOrigin = sf::Vector2f(m_spriteTexture->getSize().x / 2, m_spriteTexture->getSize().y / 2);
	m_textureRectangle = sf::IntRect(0, 0, m_spriteTexture->getSize().x, m_spriteTexture->getSize().y);
}
