#include "Comet.h"
#include <stdlib.h>

Comet::Comet()
{
}

Comet::~Comet()
{
}

bool Comet::getactive()
{
	return mAsteroidActive;
}

void Comet::alive(bool yayornay)
{
	mAsteroidActive = yayornay;
}

void Comet::editdir(float dir)
{
	m_dir = dir;
}

int Comet::getsize()
{
	return size;
}

float Comet::getdir()
{
	return m_dir;
}

void Comet::setsize(int set)
{
	size = set;
}
