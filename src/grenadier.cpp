#include "grenadier.h"
using std::cout;
grenadier::grenadier(const char* name) : soldier(name) {
	m_grenadeDmg = 20;
}

grenadier::~grenadier()
{
}

void grenadier::attack(soldier& enemy)
{
	int grenadeDmg = rand() % m_grenadeDmg;
	cout << getName() << " throw a grenade at " << enemy.getName() << " for " << grenadeDmg << " damage.\n";

	enemy.reduceHealth(grenadeDmg);
}

