#pragma once

class Missile
{
public:

	Missile();
	~Missile();

	void updateMissile(float deltaTime);

private:
	float speed = 0.0f;
	float currentLifeTime = 0.0f;
	float lifeTime = 10.0f;

};