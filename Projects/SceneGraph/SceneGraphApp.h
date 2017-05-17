////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////																													////
////																													////
////		Student Name: David Bautista																				////
////																													////
////		Program: Math Demonstration																					////
////																													////
////		Date: 14/5/2017																								////
////																													////
////		Notes: This program was originally made by aaron (the other teacher) to have a								////
////			   tank with a turret using a node system. There are some features intentionally						////
////			   missing because i ran out of time for this assignment												////
////																													////
////		Changelog:																									////
////				- Added Hitbox class, so far only accurately draws hitboxes on nodes that have a 0,0 origin			////
////				- Added projectiles																					////
////				- Added Collision detection: 																		////
////						- bullets will bounce off walls in appropriate directions									////
////						- Tank will stop moving in an axis once it hits the wall respective to it					////
////				- Added Camera																						////
////						- Camera is automatically paired with the turret, but can be prompted to snap elsewhere		////
////				- Added more obvious text for movement and shooting controls										////
////				- You can see the boundary box now																	////
////																													////
////																													////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <Vector2.h>
#include <Matrix3.h>

#include <vector>

class Node;
class SpriteNode;
class Tank;

// Colour Palette
enum Colors {
	RED = 0xff0000ff, DK_RED = 0x800000ff, YELLOW = 0xffff00ff, ORANGE = 0xff8000ff,
	GREY = 0xC0C0C0ff, DK_GREY = 0x808080ff, GREEN = 0x00ff00ff, DK_GREEN = 0x008000ff,
	CYAN = 0x00ffffff, DK_CYAN = 0x008080ff, BLUE = 0x0000ffff,
	DK_BLUE = 0x000080ff, WHITE = 0xffffffff, PURPLE = 0x8034f280
};

struct TankTracks {
	Vector2 pt;
	float rotate;
	float time;
};

struct Bullets {
	Vector2 pt;
	float rotate;
	float accel;
	float speed;
	float radius;
	float size;
	bool active;
};

struct Box {
	Vector2 pt1;
	Vector2 pt2;
};

class SceneGraphApp : public aie::Application {
public:

	SceneGraphApp();
	virtual ~SceneGraphApp();

	virtual bool startup();
	virtual void shutdown();

	void DrawLineBox(Colors colour, float x1, float y1, float x2, float y2);
	float distance(float x1, float y1, float x2, float y2);

	virtual void update(float deltaTime);
	virtual void draw();
	Box bounds;

protected:

	float m_cameraX, m_cameraY;

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	aie::Texture*		m_tankTracks = nullptr;
	aie::Texture*		m_bulletTex;
	Tank *m_tank = nullptr;

	std::vector<Node *> m_nodes;
	std::vector<TankTracks> m_tracks;
	std::vector<Bullets> m_bullets;
};