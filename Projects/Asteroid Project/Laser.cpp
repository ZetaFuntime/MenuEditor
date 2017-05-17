#include "Laser.h"



Laser::Laser()
{
}

Laser::~Laser()
{
}

bool Laser::getActive()
{
	return mLasActive;
}

float Laser::getdir()
{
	return m_dir;
}

void Laser::makeActive(bool yayornay)
{
	mLasActive = yayornay;
}

void Laser::makedir(float direction)
{
	m_dir = direction;
}
