#include "soldier.h"

soldier::soldier(const char* name)
{
	m_health = 10;
	m_name = name;
	m_weaponDmg = 10;
}

soldier::~soldier()
{
}

bool soldier::isDead()
{
	if (m_health <= 0)
	{
		return true;
	}
	return false;
}

void soldier::printHealth()
{
	cout << getName() << "'s health is " << m_health << "\n";
}

void soldier::attack(soldier& enemy)
{
	shoot(enemy);
}

void soldier::reduceHealth(float damage)
{
	m_health -= damage;
}

const char* soldier::getName()
{
	return m_name.c_str();
}

void soldier::shoot(soldier& enemy)
{
	int shotDmg = rand() % m_weaponDmg;
	cout << getName() << " shoot " << enemy.getName() << " by " << shotDmg << " damage\n";

	enemy.reduceHealth(shotDmg);
}