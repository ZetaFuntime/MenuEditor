#include "Player.h"



Player::Player()
{
	x = 520;
	y = 460;
	mScore = 0;
	radius = 30.f;
	spd = 200.f;
	mRotdir = 0.0f;
	hp = 1.0f;
	hit = false;
	mCount = 50;
	rotspd = 10.f;
}

Player::~Player()
{
}

void Player::updateScore(float score)
{
	mScore = score;
}

void Player::updateRotdir(float Rotdir)
{
	mRotdir = Rotdir;
}

float Player::getRotdir()
{
	return mRotdir;
}

float Player::getScore()
{
	return mScore;
}