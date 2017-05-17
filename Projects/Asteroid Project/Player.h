#pragma once
#include "Entity.h"
class Player : public Entity
{
public:
	Player();
	~Player();
	void updateScore(float score);
	void updateRotdir(float mRotdir);
	float getRotdir();
	float getScore();
private:
	float mRotdir;			// Which way is the player facing
	float mScore;			// Whats the player's score?
	float mCount;			// "Grace Period" count timer
	bool beenhit;			// Has player been hit
};

