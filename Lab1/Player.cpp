#include "Player.h"


void Player::MoveForward(float speed, float deltatime)
{
	pos += forward * speed * deltatime;
}

void Player::MoveRight(float speed, float deltatime)
{
	pos += glm::normalize(glm::cross(forward, up)) * speed * deltatime;
}