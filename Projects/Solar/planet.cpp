#include "planet.h"
#include "Texture.h"


float planetSizeScale = 0.000005f;

//! renderCircle - draw a circle on the screen
//! 20150520
void Planet::renderCircle(float a_centerX, float a_centerY, float a_radius, aie::Renderer2D * a_2dRenderer, Colors a_color, unsigned int a_sides)
{
	a_2dRenderer->setRenderColour(WHITE);

	if (a_sides == 0) {
		a_sides = (unsigned int)(3.14*a_radius);
	}
	a_2dRenderer->setRenderColour(a_color);

	float d_a = (float)(3.14 * 2 / (float)a_sides),
		angle = d_a;

	float startX, startY, endX, endY;
	endX = a_radius;
	endY = 0.0f;
	endX = endX + a_centerX;
	endY = endY + a_centerY;
	for (int i = 0; i != a_sides; i++)
	{
		startX = endX;
		startY = endY;
		endX = cos(angle) * a_radius;
		endY = sin(angle) * a_radius;
		endX = endX + a_centerX;
		endY = endY + a_centerY;
		angle += d_a;

		a_2dRenderer->drawLine(startX, startY, endX, endY, 1, 0);
	}
	a_2dRenderer->setRenderColour(WHITE);

}

Planet::Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, aie::Texture * textureHandle, Vector3 a_centre)
{
	float myAngle = (float) (rand() % 600) / 100.f; // randomised position in the orbit
	this->distanceFromSun = distanceFromSun;
	this->orbitTime = orbitTime;
	this->rotationTime = rotationTime;
	this->radius = radius;
	this->textureHandle = textureHandle;
	this->centre = a_centre;
	this->rotation = 0;
	this->position[0] = sin(myAngle) * distanceFromSun;
	this->position[1] = cos(myAngle) * distanceFromSun;
	this->position[2] = 0;
}

// Calculate its position in 3d spacein the orbit using the given time value
void Planet::update(float deltaTime)
{
	// angle increment for orbit modified by 
	const float myAngle = 0.1f;
	float angle = myAngle*deltaTime;
	// find the angle of orientation of the orbit around the sun
	static float timer;
	timer += deltaTime/10;

	Matrix3 rot;
	position = rot.createRotation(angle) * position;

	// find the rotation of the planet around its axis
	rotation = timer / rotationTime;

	// calculate positions of moons
	for (unsigned int i = 0; i < moons.size(); i++)
	{
		moons[i].calculatePosition(deltaTime);
	}
}
// Get its position in 3d world space units (after scaling) and put it into the 3d vector
void Planet::getPosition(Vector3* vec)
{
	const float distanceTrial = 0.000001f; // distanceScale
	*vec = position * distanceTrial;
}

void Planet::render(aie::Renderer2D* a_2dRenderer, float a_scale)
{
	const float distanceTrial = 0.000001f; // distanceScale


	a_2dRenderer->setRenderColour(WHITE);
	Vector3 vec;
	if (distanceFromSun) {
		getPosition(&vec);
	}
	vec *= a_scale;
	// modify it to the middle of the screen
	vec[0] += centre.x;
	vec[1] += centre.y;
	// draw the planet
	float spriteModifier = distanceFromSun ? 4.f : 2.f;

	// if we had moons we would go through the vector and render them here ... sort of like this
	//a_2dRenderer->drawSprite(textureHandle, position[0] * distanceTrial + centre.x, position[1] * distanceTrial + centre.y, (float)textureHandle->getWidth() / spriteModifier, (float)textureHandle->getHeight() / spriteModifier, rotation);
	// calculate positions of moons
	//for (unsigned int i = 0; i < moons.size(); i++)
	//{
	//	moons[i].render(a_2dRenderer, vec);
	//}

	a_2dRenderer->drawSprite(textureHandle, vec[0], vec[1], (float)textureHandle->getWidth() / (spriteModifier)*a_scale, (float)textureHandle->getHeight() / (spriteModifier)*a_scale, rotation);

	// and draw a circle
	if (distanceFromSun)
	vec *= a_scale;
	renderCircle(centre.x, centre.y, (distanceFromSun * distanceTrial*a_scale), a_2dRenderer);

	a_2dRenderer->setRenderColour(WHITE);
}

// get the radius of this planet
float Planet::getRadius(void)
{
	return radius;
}

void Planet::addMoon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, aie::Texture * textureHandle)
{
	moons.push_back({ distanceFromPlanet, orbitTime, rotationTime, radius, textureHandle });
}

Moon::Moon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, aie::Texture*  textureHandle)
{
	this->mdistanceFromPlanet = distanceFromPlanet;
	this->morbitTime = orbitTime;
	this->mrotationTime = rotationTime;
	this->mradius = radius;
	this->mtextureHandle = textureHandle;
	this->mrotation = 0;
}

void Moon::calculatePosition(float deltaTime)
{
	// find the angle of orientation of the orbit around the planet
	float angle = deltaTime * 3.1419f / morbitTime;

	// use trig to find the position in space relative to the planet
	mposition[0] = sin(angle) * mdistanceFromPlanet;
	mposition[1] = cos(angle) * mdistanceFromPlanet;
	mposition[2] = 0;

	// find the rotation of the moon around its axis
	mrotation = deltaTime * 360 / mrotationTime;

}

void Moon::update(float delatTime)
{
}

void Moon::render(aie::Renderer2D * a_2dRenderer, Vector3 pos)
{
}
