#include "PhysicsSimApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Matrix3.h"
#include "Vector2.h"
#include "Sphere.h"

PhysicsSimApp::PhysicsSimApp() {

}

PhysicsSimApp::~PhysicsSimApp() {

}

bool PhysicsSimApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_ball = new Sphere();
	m_ball->Translate(Vector2(300, 300));
	m_nodes.push_back(m_ball);
	return true;
}

void PhysicsSimApp::shutdown() {

	for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++) {
		delete (*iter);
	}
	m_nodes.clear();

	delete m_font;
	delete m_2dRenderer;
}

void PhysicsSimApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	int mouseX, mouseY;
	input->getMouseXY(&mouseX, &mouseY);

	Vector2 spherePos = m_ball->GetGlobalPosition();

	// grab the position of the tank and make it a vector
	Vector2 mouse = Vector2((float)mouseX, (float)mouseY) - spherePos;

	// calculate angle from vector (the vector from the tank to the mouse)
	float rads = atan2f(mouse.y, mouse.x);

	//for (auto iter = m_bullets.begin(); iter != m_bullets.end(); ++iter) {
	//	iter->time += deltaTime;
	//	iter->pt.x += cos(iter->rotate)*iter->speed*deltaTime;
	//	iter->pt.y += sin(iter->rotate)*iter->speed*deltaTime;
	//}
}

void PhysicsSimApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!

	// loop through the collection of nodes and render everything
	for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++) {
		(*iter)->Render(m_2dRenderer);
	}
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}