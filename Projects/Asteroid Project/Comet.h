#pragma once
#include "Entity.h"
class Comet : public Entity
{
public:
	Comet();
	~Comet();
	//getter
	bool getactive();
	int getsize();
	float getdir();
	
	//setter
	void alive(bool yayornay);
	void editdir(float dir);
	void setsize(int set);

private:
	bool mAsteroidActive;	// has it been created
	float m_dir;			// direction to fall down the screen
	int size;				// which size of asteroid will it be
};

