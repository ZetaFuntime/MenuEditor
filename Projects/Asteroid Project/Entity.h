#pragma once

#include "time.h"

enum Colour {
	RED = 0xff0000ff, DK_RED = 0x800000ff, YELLOW = 0xffff00ff, ORANGE = 0xff8000ff,
	GREY = 0xC0C0C0ff, DK_GREY = 0x808080ff, GREEN = 0x00ff00ff, DK_GREEN = 0x008000ff,
	CYAN = 0x00ffffff, DK_CYAN = 0x008080ff, BLUE = 0x0000ffff,
	DK_BLUE = 0x000080ff, WHITE = 0xffffffff, PURPLE = 0x8034f280
};

class Entity
{
public:
	Entity();
	~Entity();
	// getters
	float getfloat(int value);
	bool getHit();
	Colour getcolour();

	// setters
	void editx(float x_change);
	void edity(float y_change);
	void radedit(float rad_change);
	void spdedit(float spd_change);
	void rotedit(float rot_change);
	void hitedit(bool hitchange);
	void colouredit(Colour shadesofgrey);
	void hpedit(float new_hp);

	

protected:
	float x;				// Where is this thing on the x-axis		- Value [0]
	float y;				// Where is this thing on the y-axis		- Value [1]
	float radius;			// How big is the radius of this thing		- Value [2]
	float spd;				// How fast is it moving					- Value [3]
	float hp;				// How much health does it have				- Value [4]
	float rotspd;			// How fast is it spinning					- Value [5]
	bool hit;				// Has is been hit by something?
	Colour color;			// What colour is it?
};