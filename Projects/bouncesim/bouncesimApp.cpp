#include "bouncesimApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <sstream>
#include <iostream>
#include <cmath>
#include <Utility.h>
#include <math.h>
#include <stdlib.h>

bouncesimApp::bouncesimApp() {

}

bouncesimApp::~bouncesimApp() {

}

bool bouncesimApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_angryTex = new aie::Texture("./textures/angery.png");
	bounds.pt1 = Vector2((float) 10,(float) 10);
	bounds.pt2 = Vector2((float)getWindowWidth() - 40.f,(float)getWindowHeight() - 10.f);
	return true;
}

void bouncesimApp::shutdown() {

	delete m_font;
	delete m_angryTex;
	delete m_2dRenderer;
}

float bouncesimApp::distance(float x1, float y1, float x2, float y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

void bouncesimApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	input->getMouseXY(&mouseX, &mouseY);
	float b_TimeInterval = 0.25f;
	static float currentTime;
	currentTime += deltaTime;

	pointX = bounds.pt2.x / 2;
	pointY = bounds.pt2.y / 2;
	Vector2 point = Vector2(pointX, pointY);
	Vector2 radpt = Vector2(mouseX - pointX, mouseY - pointY);
	rads = atan2f(radpt.y, radpt.x);
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT) && currentTime > b_TimeInterval) {
		currentTime = 0;
		Ball bb;
		bb.pt = point;
		bb.radius = rand() % 50 + 50.f;
		bb.rads = rads;
		bb.speed = distance(mouseX,mouseY,pointX,pointY);
		bb.accel = 0.5f;
		bb.active = true;
		m_ball.push_back(bb);
	}

	for (unsigned int k = m_ball.size(); k--;) {
		if (!m_ball[k].active) {
			m_ball.erase(m_ball.begin() + k);
		}
	}
}

void bouncesimApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	//draw the boundary box
	m_2dRenderer->setRenderColour(CYAN);
	m_2dRenderer->drawLine(bounds.pt1.x, bounds.pt1.y, bounds.pt1.x, bounds.pt2.y);			// Left Side
	m_2dRenderer->drawLine(bounds.pt1.x, bounds.pt2.y, bounds.pt2.x, bounds.pt2.y);			// Top Side
	m_2dRenderer->drawLine(bounds.pt2.x, bounds.pt2.y, bounds.pt2.x, bounds.pt1.y);			// Right Side
	m_2dRenderer->drawLine(bounds.pt1.x, bounds.pt1.y, bounds.pt2.x, bounds.pt1.y);			// Bottom Side
	for (auto iter = m_ball.begin(); iter != m_ball.end(); ++iter) {
		m_2dRenderer->setRenderColour(WHITE);
		m_2dRenderer->drawSprite(m_angryTex, iter->pt.x, iter->pt.y, iter->radius, iter->radius);
	}
	//draw a line between the point and the mouse
	m_2dRenderer->setRenderColour(BLUE);
	m_2dRenderer->drawLine(pointX, pointY, mouseX, mouseY);

	
	//draw a line between the ball and every other ball, for every ball
	m_2dRenderer->setRenderColour(WHITE);
	for (auto iter = m_ball.begin(); iter != m_ball.end(); ++iter) {
		for (unsigned int k = m_ball.size(); k--;) {
			m_2dRenderer->drawLine(iter->pt.x, iter->pt.y, m_ball[k].pt.x, m_ball[k].pt.y);
		}
	}
	// output some text, uses the last used colour
	m_2dRenderer->setRenderColour(WHITE);
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	std::ostringstream os;
	//os << " # of balls:["<< m_ball.size() << "]";
	//m_2dRenderer->drawText(m_font, os.str().c_str(), 0, 700);

	os << "r:["<< rads << "] spd:[" << distance(mouseX, mouseY, pointX, pointY) << "]";
	m_2dRenderer->drawText(m_font, os.str().c_str(), mouseX, mouseY);
	for (auto iter = m_ball.begin(); iter != m_ball.end(); ++iter) {
		std::ostringstream os;
		//os << " Spd:[" << iter->speed << "]";
		os << iter->speed;
		m_2dRenderer->drawText(m_font, os.str().c_str(), iter->pt.x, iter->pt.y);
	}
	// done drawing sprites
	m_2dRenderer->end();
}