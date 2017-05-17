#include "Asteroid_ProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>

Asteroid_ProjectApp::Asteroid_ProjectApp() {

	//m_cameraX = m_cameraY = 0;
	mGameIsOver = false;
	m_TimeInterval = 3.0f;
	Ball.editx(-1.f);
	Ball.radedit(40.f);
	Ball.hitedit(false);
	mTimer = 0.f;
}

bool Asteroid_ProjectApp::startup() {

	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_playership = new aie::Texture("./textures/fighter-01.png");
	m_smallrock = new aie::Texture("./textures/rock_small.png");
	m_medrock = new aie::Texture("./textures/rock_medium.png");
	m_bigrock = new aie::Texture("./textures/rock_large.png");
	m_points = new aie::Texture("./textures/trophy.png");
	m_background = new aie::Texture("./textures/background.png");
	m_death2 = new aie::Texture("./textures/Explosion2.png");
	m_laser = new aie::Texture("./textures/Laser1.png");

	p1.editx((float)(getWindowWidth() / 2));
	p1.edity((float)(getWindowHeight() / 2));

	placeBallInPlay();

	return true;
}

void Asteroid_ProjectApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete m_playership;
	delete m_smallrock;
	delete m_medrock;
	delete m_bigrock;
	delete m_background;
	delete m_death2;
	delete m_laser;

}

// if the ball is not in play place it in play
void Asteroid_ProjectApp::placeBallInPlay()
{
	if (Ball.getHit()) return;

	int countTries = 0;

	while (true) {

		if (countTries++ > 10000) break;

		int x = rand() % (int)(getWindowHeight() - 40) + 20 + p1.getfloat(0);
		int y = rand() % (int)(getWindowWidth() - 40) + 20 + p1.getfloat(1);

		// not on the player
		if (distance(p1.getfloat(0), p1.getfloat(1), x, y) < p1.getfloat(2) + 20) continue;

		// nor close to any comet
		bool areaOk = true;
		for (unsigned int i = 0; i < mAst.size(); ++i) {
			if (distance(mAst[i].getfloat(0), mAst[i].getfloat(1), x, y) < mAst[i].getfloat(2) + 20) areaOk = false;
		}
		if (!areaOk) continue;

		// SUCCESS
		Ball.editx(x);
		Ball.edity(y);
		Ball.hitedit(true);
		break;
	}
}

// distance between (x1, y1) and (x2, y2)
float Asteroid_ProjectApp::distance(float x1, float y1, float x2, float y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

void Asteroid_ProjectApp::update(float deltaTime) {

	//Boundary();
	//m_cameraX = p1.getfloat(0);
	//m_cameraY = p1.getfloat(1);
	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	// Place ball in play
	if (!Ball.getHit()) {
		placeBallInPlay();
	}
	// do we create another laser
	if (input->isKeyDown(aie::INPUT_KEY_SPACE))
		createlaser(deltaTime);

	// do we create another comet
	testCreateAsteroid(deltaTime);

	// update comet
	for (unsigned int i = mAst.size(); i--;)
		asteroidUpdate(&mAst[i], deltaTime);

	for (unsigned int i = mlas.size(); i--;)
		laserUpdate(&mlas[i], deltaTime);

	// now erase bullets out of screen
	for (unsigned int i = mlas.size(); i--;) {
		if (mlas[i].getActive()) continue;
		mlas.erase(mlas.begin() + i);
	}

	// now erase all comets that are outside the screen or killed
	for (unsigned int i = mAst.size(); i--;) {
		if (mAst[i].getactive()) continue;
		mAst.erase(mAst.begin() + i);
	}

	//what does player 1 want to do?
	if (input->isKeyDown(aie::INPUT_KEY_A))
		p1.updateRotdir(p1.getRotdir() + p1.getfloat(5) * deltaTime);						//This controls rotation in the CCW direction

	if (input->isKeyDown(aie::INPUT_KEY_D))
		p1.updateRotdir(p1.getRotdir() - p1.getfloat(5) * deltaTime);						//This controls rotation in the CW direction

	if (input->isKeyDown(aie::INPUT_KEY_W)) {
		p1.editx(p1.getfloat(0) + cos(p1.getRotdir())*p1.getfloat(3)*deltaTime);
		p1.edity(p1.getfloat(1) + sin(p1.getRotdir())*p1.getfloat(3)*deltaTime);	//This controls movement towards the direction player is facing
	}
	if (input->isKeyDown(aie::INPUT_KEY_S)) {
		p1.editx(p1.getfloat(0) - cos(p1.getRotdir())*p1.getfloat(3 )*deltaTime);
		p1.edity(p1.getfloat(1) - sin(p1.getRotdir())*p1.getfloat(3)*deltaTime);	//This controls movement away from the direction the player is facing
	}

	Ball.rotedit(Ball.getfloat(5) + 0.5f);

	//if (input->isKeyDown(aie::INPUT_KEY_UP))
	//	m_cameraY += 500.0f * deltaTime;
	//
	//if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	//	m_cameraY -= 500.0f * deltaTime;
	//
	//if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	//	m_cameraX -= 500.0f * deltaTime;
	//
	//if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	//	m_cameraX += 500.0f * deltaTime;
	//
	//if (input->isKeyDown(aie::INPUT_KEY_C))
	//	m_cameraX = m_cameraY = 0;
}

void Asteroid_ProjectApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	m_2dRenderer->setCameraPos(p1.getfloat(0)- 540, p1.getfloat(1) - 360);

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	// the ball is placed first
	if (Ball.getHit()) {
		m_2dRenderer->setRenderColour(WHITE); // other way
		m_2dRenderer->drawSprite(m_points, Ball.getfloat(0) , Ball.getfloat(1), Ball.getfloat(2), Ball.getfloat(2), mTimer += 0.025f);
		//m_2dRenderer->drawCircle(Ball.getfloat(0), Ball.getfloat(1), Ball.getfloat(2));
	}
	// the player
	m_2dRenderer->setRenderColour((!mGameIsOver) ? ((p1.getHit()) ? RED : WHITE) : WHITE); // show damage if been hit
	m_2dRenderer->drawSprite((!mGameIsOver) ? m_playership : m_death2, 
		p1.getfloat(0), p1.getfloat(1), 65.0f, 65.0f, p1.getRotdir(), 1.0f);

	// the comets
	for (unsigned int i = 0; i < mAst.size(); ++i) {
		m_2dRenderer->setRenderColour(mAst[i].getcolour());
		m_2dRenderer->drawSprite((mAst[i].getsize() == 1) ? m_smallrock : ((mAst[i].getsize() == 2) ? m_medrock : m_bigrock),
			mAst[i].getfloat(0), mAst[i].getfloat(1), mAst[i].getfloat(2), mAst[i].getfloat(2), mAst[i].getfloat(1) / 100);
	}

	// the lasers
	for (unsigned int i = 0; i < mlas.size(); ++i) {
		m_2dRenderer->setRenderColour(mlas[i].getcolour());
		m_2dRenderer->drawSprite(m_laser,mlas[i].getfloat(0), mlas[i].getfloat(1), mlas[i].getfloat(2), mlas[i].getfloat(2), mlas[i].getdir());
	}

	// output some text, uses the last used colour
	if (mGameIsOver) {
		m_2dRenderer->setRenderColour(YELLOW);
		std::ostringstream os;
		os << "Game Over :: Press ESC to quit";
		m_2dRenderer->drawText(m_font, os.str().c_str(),(int)p1.getfloat(0) - 540,(int)p1.getfloat(1) - 360);
	}
	else {
		int p1x = p1.getfloat(0);
		int p1y = p1.getfloat(1);
		m_2dRenderer->setRenderColour(WHITE);
		std::ostringstream os;
		os << "Press ESC to quit:: [";
		os << "]" << p1.getfloat(0) << "][" << p1.getfloat(1) << "]";
		os << "[" << Ball.getfloat(0) << "][" << Ball.getfloat(1) << "]";
		m_2dRenderer->drawText(m_font, os.str().c_str(),p1x - 540,p1y - 360);
	}

	// done drawing sprites
	m_2dRenderer->end();
}

// do we create asteroids (and do we hit the ball/powerup)
void Asteroid_ProjectApp::testCreateAsteroid(float a_deltaTime)
{
	static float currentTime, stopCreateTime;
	currentTime += a_deltaTime;
	const float decreaseInterval = 1.0f;
	static float addTime;

	addTime += a_deltaTime;
	if (addTime > decreaseInterval) {
		addTime = 0;
		// lower the time of the next comet
		m_TimeInterval = max(0.2f, m_TimeInterval - 0.2f);
	}

	// have we hit the ball ..... yehhh
	if (distance(p1.getfloat(0), p1.getfloat(1), Ball.getfloat(0), Ball.getfloat(1)) <  Ball.getfloat(2)) {
		//radius down
		float Rad_in = max(Ball.getfloat(2), p1.getfloat(2) - 1.f);
		p1.radedit(Rad_in);
		//ball is out of play
		Ball.hitedit(false);
		// score
		p1.updateScore(1);
		// stop creation
		stopCreateTime = 1.f;
		// increase player speed
		float Spd_in = p1.getfloat(3) + 5.0f;
		p1.spdedit(Spd_in);
	}

	stopCreateTime = max(0.f, stopCreateTime - a_deltaTime);
	if (stopCreateTime) return;
	if (mAst.size() < 4) {
		//think about creation
		if (currentTime < m_TimeInterval) return;
		currentTime = 0;
		Comet cmt;
		cmt.editx((float)((rand() % (getWindowWidth() - 50) + 25 + p1.getfloat(0))));
		cmt.edity((float)(getWindowHeight() - 50) + 25 + p1.getfloat(1));
		// active
		cmt.alive(true);
		cmt.spdedit((float)(rand() % 400 + 25));
		cmt.setsize((cmt.getfloat(3) < 300) ? ((cmt.getfloat(3) < 180) ? 3 : 2) : 1);
		//radius
		cmt.radedit((cmt.getsize() == 3) ? 60.f : ((cmt.getsize() == 2) ? 40.f : 20.f));
		//health
		cmt.hpedit((cmt.getsize() == 3) ? 200.f : ((cmt.getsize() == 2) ? 150.f : 100.f));
		int randDir = rand() % 3;
		float randAngle = rand() % 3 + 0.25f;
		switch (randDir) {
		case 0: randAngle = 0;					break;
		case 1: randAngle = randAngle * -1;		break;
		default:								break;
		}
		cmt.editdir(randAngle);
		// add to vector
		mAst.push_back(cmt);
	}
}

void Asteroid_ProjectApp::createlaser(float a_deltaTime)
{
	static float currentTime;
	currentTime += a_deltaTime;
	l_TimeInterval = 0.01f;
	if (currentTime < l_TimeInterval) return;
	currentTime = 0;
	Laser las;
	las.editx(p1.getfloat(0));
	las.edity(p1.getfloat(1));
	// active
	las.makeActive(true);
	las.spdedit(800.f);
	//radius
	las.radedit(20.f);
	las.makedir(p1.getRotdir() + (rand() % 8)/20.f);
	las.colouredit(WHITE);
	// add to vector
	mlas.push_back(las);
}

void Asteroid_ProjectApp::laserUpdate(Laser *a_las, float a_deltaTime)
{
	// Movement yeahboi
	a_las->edity(a_las->getfloat(1) + sin(a_las->getdir())*a_las->getfloat(3)*a_deltaTime);
	a_las->editx(a_las->getfloat(0) + cos(a_las->getdir())*a_las->getfloat(3)*a_deltaTime);

	// are we outside the screen
	if (a_las->getfloat(1) < 0 || a_las->getfloat(1) > getWindowHeight() || a_las->getfloat(0) < 0 || a_las->getfloat(0) > getWindowWidth())
		a_las->makeActive(false);
}

void Asteroid_ProjectApp::asteroidUpdate(Comet *a_ast, float a_deltaTime)
{
	// coming down or left or right
	a_ast->edity(a_ast->getfloat(1) - a_ast->getfloat(3)*a_deltaTime);
	a_ast->editx(a_ast->getfloat(0) - a_ast->getfloat(3)*a_ast->getdir()*a_deltaTime);
																											
	if (distance(p1.getfloat(0), p1.getfloat(1), a_ast->getfloat(0), a_ast->getfloat(1)) < a_ast->getfloat(2)) {
		// delete the comet
		a_ast->alive(false);
	}

	//for (int i = 0; i < )
	int colorD = (a_ast->getfloat(4) >= 100) ? 5 : (a_ast->getfloat(4) > 74 && a_ast->getfloat(4) < 100) ? 4 : (a_ast->getfloat(4) > 49 && a_ast->getfloat(4) < 75) ? 3 : (a_ast->getfloat(4) > 25 && a_ast->getfloat(4) < 50) ? 2 : 1;
	switch (colorD) {
	case 4:		a_ast->colouredit(YELLOW);		break;
	case 3:		a_ast->colouredit(ORANGE);		break;
	case 2:		a_ast->colouredit(RED);		break;
	case 1:		a_ast->colouredit(DK_RED);		break;
	default:	a_ast->colouredit(WHITE);		break;
	}
	// Is the player dead yet?
	if (p1.getfloat(4) == 0) {
		mGameIsOver = true;
	}
	// are we outside the screen
	if (a_ast->getfloat(4) < 0)
		p1.updateScore(p1.getScore() + 1);
	if (a_ast->getfloat(1) < 0 || a_ast->getfloat(1) > getWindowHeight() || a_ast->getfloat(0) < 0 || a_ast->getfloat(0) > getWindowWidth())
		a_ast->alive(false);
}