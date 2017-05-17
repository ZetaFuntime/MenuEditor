#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <vector>
#include "Matrix3.h"
#include "Vector3.h"
#include <memory>

using std::vector;
const float distanceScale = 0.00000001f;
enum Colors {
	RED = 0xff0000ff, DK_RED = 0x800000ff, YELLOW = 0xffff00ff, ORANGE = 0xff8000ff, GREY = 0xC0C0C0ff, DK_GREY = 0x808080ff, GREEN = 0x00ff00ff,
	DK_GREEN = 0x008000ff, CYAN = 0x00ffffff, DK_CYAN = 0x008080ff, BLUE = 0x0000ffff, DK_BLUE = 0x000080ff, WHITE = 0xffffffff, PURPLE = 0x8034f2,
	TRANS_RED = 0xff000040
};

class Moon
{
public:
	// Distance is in units of km (kilometers) and time is in units of earth days
	Moon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, aie::Texture*  textureHandle);

	// Calculate its position in 3d space relative to the planet in the orbit using the given time value
	void calculatePosition(float deltaTime);

	// Calculate its position in 3d spacein the orbit using the given time value
	void update(float delatTime);

	// Render it to the screen
	void render(aie::Renderer2D*, Vector3 pos);

private:
	float	mdistanceFromPlanet;					// distance from its planet
	float	morbitTime;								// time it takes to complete 1 orbit
	float	mrotationTime; 							// time it takes to spin 360 degrees
	float	mradius;								// radius of the moon itself
	aie::Texture* mtextureHandle;					// the texture used for rendering
	Vector3 mposition;								// its position in 3d space relative to the planet
	float	mrotation;								// its rotation around its axis
};

class Planet
{
public:
	// Distance is in units of km (kilometers) and time is in units of earth days (365.25 orbit time for earth)
	Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, aie::Texture * textureHandle, Vector3 centre);

	// Calculate its position in 3d spacein the orbit using the given time value
	void update(float delatTime);

	// Render it to the screen
	void render(aie::Renderer2D*, float scale);

	// Get its position in 3d world space units (after scaling) and put it into the 3d vector
	void getPosition(Vector3* vec);

	// get the radius of this planet
	float getRadius();

	// add a moon to this planet
	void addMoon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, aie::Texture* textureHandle);

private:
	float distanceFromSun;									// distance from the sun
	float orbitTime;										// time it takes to complete 1 orbit
	float rotationTime;										// time it takes to spin 360 degrees
	float radius;											// radius of the planet itself
	float angle;											// current angle around the sun
	aie::Texture * textureHandle;							// the texture used for rendering
	Vector3 position;										// its position in 2d space
	float rotation;											// its rotation around its axis
	std::vector<Moon> moons;								// list of moons attached to this planet
	Vector3 centre;											// its position in 2d space to the axis
	void renderCircle(float centerX, float centerY, float radius, aie::Renderer2D * a_2dRenderer, Colors color = TRANS_RED, unsigned int sides = 100); // draw the orbit
};