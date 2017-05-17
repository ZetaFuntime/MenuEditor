#pragma once
#include "Entity.h"
class Laser :
	public Entity
{
public:
	Laser();
	~Laser();
	bool getActive();
	float getdir();
	void makeActive(bool yayornay);
	void makedir(float direction);
private:
	bool mLasActive;
	float m_dir;
	float m_dist;
	float damage;
};

