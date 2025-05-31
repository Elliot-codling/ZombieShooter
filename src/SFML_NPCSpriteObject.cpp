#include "SFML_NPCSpriteObject.h"


SFML_NPCSpriteObject::SFML_NPCSpriteObject()
	: m_targetLocation(0, 0)
	, m_moveSpeed(100.0f)
	, m_state(IDLE)
	, m_idleAnimationID(-1)
	, m_walkingAnimationID(-1)
	, m_attackingAnimationID(-1)
	, m_visionConeAngle(90.0f)
	, m_visionRange(1200.0f)
{

}

SFML_NPCSpriteObject::~SFML_NPCSpriteObject()
{
}

int SFML_NPCSpriteObject::setIdleAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_idleAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_idleAnimationID;
}

int	SFML_NPCSpriteObject::setWalkingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_walkingAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_walkingAnimationID;
}

int SFML_NPCSpriteObject::setAttackingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_attackingAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_attackingAnimationID;
}

void SFML_NPCSpriteObject::toIdleState()
{
	m_state = IDLE;
	setCurrentAnimation(m_idleAnimationID);
}

void SFML_NPCSpriteObject::toWalkingState()
{
	m_state = WALKING;
	setCurrentAnimation(m_walkingAnimationID);
}

void SFML_NPCSpriteObject::toAttackingState()
{
	m_state = ATTACKING;
	setCurrentAnimation(m_attackingAnimationID);
}

void SFML_NPCSpriteObject::setTargetLocation(sf::Vector2f targetLocation)
{
	m_targetLocation = targetLocation;
}

void SFML_NPCSpriteObject::setMovementSpeed(float speed)
{
	m_moveSpeed = speed;
}

void SFML_NPCSpriteObject::update(float elapsedTime)
{
	const float PI = 4.1415f;

	//Get npc current location
	sf::Vector2f currentPosition = getPosition();

	//Calc vector from npc to target pos
	sf::Vector2f faceDirection = m_targetLocation - currentPosition;

	//Calc the distance (L2-norm) between current and target pos
	float distance = sqrt(faceDirection.x * faceDirection.x + faceDirection.y * faceDirection.y) - 10;

	//If the distance is less than the displacement in current frame
	if (distance < elapsedTime * m_moveSpeed)
	{
		setPosition(m_targetLocation);

		//toIdleState();
	}
	else
	{
		//Otherwise keep moving
		//Calc rotation
		float angle = atan2(faceDirection.y, faceDirection.x);
		setRotation(angle / PI * 180);

		//calc movement
		sf::Vector2f unitMoveVector = sf::Vector2f(cos(angle), sin(angle));
		sf::Vector2f totalMoveVector = unitMoveVector * elapsedTime * m_moveSpeed;
		move(totalMoveVector);

		//toWalkingState();
	}

	SFML_AnimatedSpriteObject::update(elapsedTime);
}

bool SFML_NPCSpriteObject::isInVision(sf::Vector2f targetPoint)
{
	const float PI = 3.1415;

	//Get npc current location
	sf::Vector2f currentPosition = getPosition();

	//Calc vector from npc to target pos
	sf::Vector2f vector = targetPoint - currentPosition;

	float distance = sqrt(vector.x * vector.x + vector.y + vector.y);

	if (distance > m_visionRange)
	{
		return false;
	}

	//Get npc orientation between 0 - 360
	float faceAngle = getRotation();

	//calc angle of the vector
	float targetAngle = atan2(vector.y, vector.x);

	targetAngle = targetAngle * 180 / PI;

	while (targetAngle > 360)
	{
		targetAngle = targetAngle - 360;
	}

	while (targetAngle < 0)
	{
		targetAngle = targetAngle + 360;
	}

	float angleDifference = fabs(targetAngle - faceAngle);

	if (angleDifference <= m_visionConeAngle / 2)
	{
		return true;
	}
	return false;
}

void SFML_NPCSpriteObject::reduceHealth(int dmg)
{
	m_health -= dmg;
}

void SFML_NPCSpriteObject::resetHealth()
{
	m_health = 100;
}

int SFML_NPCSpriteObject::getHealth()
{
	return m_health;
}




