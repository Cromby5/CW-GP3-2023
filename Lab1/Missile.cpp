#include "Missile.h"

#include <iostream>

Missile::Missile()
{
}

Missile::~Missile()
{
}

void Missile::updateMissile(float deltaTime)
{
	currentLifeTime += 0.10f * deltaTime;
	std::cout << currentLifeTime << std::endl;
}
