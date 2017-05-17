#pragma once

#include "Application.h"
#include "Texture.h"
#include "Renderer2D.h"
#include <Vector2.h>
#include <Matrix3.h>

#include <vector>

enum Colors {
	RED = 0xff0000ff, DK_RED = 0x800000ff, YELLOW = 0xffff00ff, ORANGE = 0xff8000ff,
	GREY = 0xC0C0C0ff, DK_GREY = 0x808080ff, GREEN = 0x00ff00ff, DK_GREEN = 0x008000ff,
	CYAN = 0x00ffffff, DK_CYAN = 0x008080ff, BLUE = 0x0000ffff,
	DK_BLUE = 0x000080ff, WHITE = 0xffffffff, PURPLE = 0x8034f280
};

struct Ball {
	Vector2 pt;
	float speed;
	float accel;
	float rads;
	float radius;
	bool active;
};

struct Box {
	Vector2 pt1;
	Vector2 pt2;
	float speed;
	float accel;
	float rads;
};

struct Menu {
	bool circlemake;
	bool squaremake;
	bool changebound;
};

struct Point {
	Vector2 pt;
};

class bouncesimApp : public aie::Application {
public:

	bouncesimApp();
	virtual ~bouncesimApp();

	virtual bool startup();
	virtual void shutdown();

	float distance(float x1, float y1, float x2, float y2);

	virtual void update(float deltaTime);
	virtual void draw();

	Box bounds;
	float pointX;
	float pointY;
	int count;
	int mouseX;
	int mouseY;
	float rads;

protected:
	
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	aie::Texture*		m_angryTex;

	std::vector<Ball> m_ball;
};