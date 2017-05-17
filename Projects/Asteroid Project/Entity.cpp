#include "Entity.h"
#include <iostream>
#include <Windows.h>

Entity::Entity()
{
}

Entity::~Entity()
{
}

float Entity::getfloat(int value)
{
	float temp;

	switch (value){
	case 0:		temp = x;		break;
	case 1:		temp = y;		break;
	case 2:		temp = radius;	break;
	case 3:		temp = spd;		break;
	case 4:		temp = hp;		break;
	case 5:		temp = rotspd;	break;
	default:	temp = 0;		break;
	}
	return temp;
}

bool Entity::getHit()
{
	return hit;
}

void Entity::edity(float y_change)
{
	y = y_change;
}

void Entity::editx(float x_change)
{
	x = x_change;
}

void Entity::radedit(float rad_change)
{
	radius = rad_change;
}

void Entity::spdedit(float spd_change)
{
	spd = spd_change;
}

void Entity::rotedit(float rot_change)
{
	rotspd = rot_change;
}

void Entity::hitedit(bool hitchange)
{
	hit = hitchange;
}

void Entity::colouredit(Colour shadesofgrey)
{
	color = shadesofgrey;
}

void Entity::hpedit(float new_hp)
{
	hp = new_hp;
}

Colour Entity::getcolour()
{
	return color;
}