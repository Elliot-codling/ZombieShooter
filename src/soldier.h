#pragma once
#include <iostream>
using namespace std;

class soldier
{
public:
	soldier(const char* name);
	~soldier();

	bool isDead();
	void printHealth();
	void attack(soldier& enemy);
	const char* getName();
	void reduceHealth(float damage);

private:
	void shoot(soldier& enemy);
	string m_name;
	int m_weaponDmg;
	int m_health;
};


