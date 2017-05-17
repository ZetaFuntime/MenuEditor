#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <Windows.h>
#include <vector>
#include "Audio.h"
#include "Texture.h"
#include "Comet.h"
#include "Laser.h"
#include "Powerup.h"
#include "Player.h"

using std::vector;


class Asteroid_ProjectApp : public aie::Application {
public:

	Asteroid_ProjectApp();

	virtual bool startup();
	virtual void shutdown();

	//void Boundary();

	void placeBallInPlay();

	float distance(float x1, float y1, float x2, float y2);

	virtual void update(float deltaTime);
	virtual void draw();

	void testCreateAsteroid(float a_deltaTime);
	void createlaser(float a_deltaTime);

	void laserUpdate(Laser * a_las, float a_deltaTime);

	void asteroidUpdate(Comet * a_ast, float a_deltaTime);

protected:

	float p1front;
	float xMax;
	float yMax;
	float pitchlvl;
	bool mGameIsOver;
	bool GameOverSequence;
	float m_TimeInterval;
	float l_TimeInterval;
	float mTimer;
	vector <Comet> mAst;
	vector <Laser> mlas;
	Player p1;
	Entity Ball;
	Powerup Powup;

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	// Textures used

	aie::Texture*		m_playership;
	aie::Texture*		m_smallrock;
	aie::Texture*		m_medrock;
	aie::Texture*		m_bigrock;
	aie::Texture*		m_points;
	aie::Texture*		m_laser;
	aie::Texture*		m_background;
	aie::Texture*		m_death2;

	float m_cameraX, m_cameraY;
};