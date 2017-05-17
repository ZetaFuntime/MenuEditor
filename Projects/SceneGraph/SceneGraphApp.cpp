#define _USE_MATH_DEFINES
#include "SceneGraphApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Utility.h>
#include "Node.h"
#include "SpriteNode.h"
#include "Tank.h" 
#include <math.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>

SceneGraphApp::SceneGraphApp() {
	
}

SceneGraphApp::~SceneGraphApp() {
}

bool SceneGraphApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_tankTracks = new aie::Texture("./sceneGraph/textures/tankTracks.png");
	m_bulletTex = new aie::Texture("./sceneGraph/textures/angery.png");
	m_tank = new Tank();
	m_tank->Translate(Vector2((float)getWindowWidth()/2, (float)getWindowHeight()/2));
	m_tank->SetBoundCenter(Vector2((float)getWindowWidth() / 2, (float)getWindowHeight() / 2));
	m_nodes.push_back(m_tank);

	bounds.pt1 = Vector2(0 +(float)getWindowWidth()*0.25f, 0 +(float)getWindowHeight()*0.25f);
	bounds.pt2 = Vector2((float)getWindowWidth()*0.75f, (float)getWindowHeight()*0.75f);

	return true;
}



void SceneGraphApp::shutdown() {

	for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++) {
		delete (*iter);
	}
	m_nodes.clear();
	
	delete m_font;
	delete m_2dRenderer;
	delete m_tankTracks;
}

void SceneGraphApp::DrawLineBox(Colors colour, float x1, float y1, float x2, float y2) 
{
	m_2dRenderer->setRenderColour(colour);
	m_2dRenderer->drawLine(x1, y1, x1, y2);		// Left Side
	m_2dRenderer->drawLine(x1, y2, x2, y2);		// Top Side
	m_2dRenderer->drawLine(x2, y2, x2, y1);		// Right Side
	m_2dRenderer->drawLine(x1, y1, x2, y1);		// Bottom Side
}

float SceneGraphApp::distance(float x1, float y1, float x2, float y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

void SceneGraphApp::update(float deltaTime) {

	static float sDx, sDy;
	static float currentTime;
	static float m_timer;
	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	// grab mouse coords
	int mouseX, mouseY;
	input->getMouseXY(&mouseX, &mouseY);

	// Get the position of the tank
	Vector2 tankPos = m_tank->GetGlobalPosition();

	// grab the position of the tank and make it a vector
	Vector2 mouse = Vector2((float)mouseX, (float)mouseY) - tankPos;

	// Timer for activating camera switches
	m_timer += deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_SPACE) && m_timer >= 1.f) {
		m_timer = 0;
		m_tank->SwitchCamera();
	}
	Vector2 CameraPos = m_tank->GetGlobalCameraPos();
	m_cameraX = CameraPos.x - (float)getWindowWidth()/2;
	m_cameraY = CameraPos.y - (float)getWindowHeight()/2;

	// calculate angle from vector (the vector from the tank to the mouse)
	float m_rads = atan2f(mouse.y, mouse.x);

	// the turret only follows the tank
	m_tank->SetTurretRotate(m_rads);


	// || Tank Tracks || - these were originally aaron's code

	if (abs(sDx - tankPos.x) + abs(sDy - tankPos.y) > 5) {
		TankTracks tt;

		tt.pt = m_tank->GetLocalPosition();
		tt.rotate = m_tank->GetBaseRotate();
		tt.time = 0.0f;

		m_tracks.push_back(tt);
		sDx = tankPos.x;
		sDy = tankPos.y;
	}

	// clear 'old' tank tracks - first update the timing
	for (auto iter = m_tracks.begin(); iter != m_tracks.end(); ++iter) {
		iter->time += deltaTime;
	}

	// then erase the ones that have been around a while counting backwards
	for (unsigned int k = m_tracks.size(); k--;) {
		if (m_tracks[k].time >= 5.0f) {
			m_tracks.erase(m_tracks.begin()+k);
		}
	}

	// || Projectiles ||

	currentTime += deltaTime;				// Check time since value resetted
	float TimeInterval = 0.1f;				// Bullet time creation buffer

	// If it has been long enough, shoot another bullet
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		currentTime = 0;
		Bullets bb;
		bb.pt = m_tank->GetLocalPosition();		// shoot from the tank
		bb.rotate = m_rads;						// according to where the mouse is pointing
		bb.accel = 2.f;
		bb.speed = 200.f;
		bb.size = rand() % 25 + 50.f;			// random size of bullet
		bb.radius = bb.size / 2;				// radius calculation for collision detection
		bb.active = true;						// is now "Alive"
		m_bullets.push_back(bb);
	}

	// Iterate through all active bullets and update their angle, speed and location
    for (auto iter = m_bullets.begin(); iter != m_bullets.end(); ++iter) {

    		// Checks the bullets to see if they raced off elsewhere, if so kill them
    		if (iter->pt.y < bounds.pt1.y - 20.f|| iter->pt.y > bounds.pt2.y + 20.f|| iter->pt.x < bounds.pt1.x - 20.f|| iter->pt.x > bounds.pt2.x + 20.f) iter->active = false;
    
    		// Adjusts angle based off incidence
    		if (iter->pt.x  < bounds.pt1.x + iter->radius || iter->pt.x > bounds.pt2.x - iter->radius)
    			(iter->rotate < 0) ? iter->rotate = (3.14159f + iter->rotate)*-1 : iter->rotate = 3.14159f - iter->rotate;	// If in X-axis, creates the angle of deflection
    		if (iter->pt.y  < bounds.pt1.y + iter->radius || iter->pt.y > bounds.pt2.y - iter->radius)
    			iter->rotate = (iter->rotate)*-1;																			// Otherwise, it flips the angle
	
			// Accelerate projectile the longer it has been active
    		iter->speed += iter->accel;
	
    		// Movement algorithm
			iter->pt.y += sin(iter->rotate)*deltaTime*iter->speed;
			iter->pt.x += cos(iter->rotate)*deltaTime*iter->speed;
    }
	
	// If bullets are inactive, delete them
	for (unsigned int k = m_bullets.size(); k--;) {
		if (m_bullets[k].active == false) {
			m_bullets.erase(m_bullets.begin() + k);
		}
	}

	// || Tank Base movement calculation ||

	float speed = 100.f;
	// Movement forwards or Backwards
	if (input->isKeyDown(aie::INPUT_KEY_W) || input->isKeyDown(aie::INPUT_KEY_S)) {
		float dx = cos(m_tank->GetBaseRotate())*deltaTime*speed;
		float dy = sin(m_tank->GetBaseRotate())*deltaTime*speed;

		Vector2 tankPos = m_tank->GetGlobalPosition();
		if (tankPos.x + dx < bounds.pt1.x + 25.f || tankPos.x + dx > bounds.pt2.x - 25.f) dx = 0;				// Note: If the tank moves into an object, it negates movement
		if (tankPos.y + dy < bounds.pt1.y + 25.f || tankPos.y + dy > bounds.pt2.y - 25.f) dy = 0;				//		 in the direction it's not allowed to go into

		(input->isKeyDown(aie::INPUT_KEY_W))? m_tank->Translate({  dx, dy }) : m_tank->Translate({ -dx,-dy });
	}

	// Left or Right Rotation
	if (input->isKeyDown(aie::INPUT_KEY_A) || input->isKeyDown(aie::INPUT_KEY_D)) {
		float tankturn = m_tank->GetBaseRotate();
		m_tank->SetBaseRotate((input->isKeyDown(aie::INPUT_KEY_A))? tankturn += 0.05f : tankturn -= 0.05f);
	}
	
	// Update all nodes active
	for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++)
	{
		(*iter)->Update(deltaTime);
	}
}

void SceneGraphApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	m_2dRenderer->setRenderColour(0xffffff40);
	for (auto iter = m_tracks.begin(); iter != m_tracks.end(); ++iter) {
		m_2dRenderer->drawSprite(m_tankTracks, iter->pt.x, iter->pt.y, (float)m_tankTracks->getWidth(), (float)m_tankTracks->getHeight(), iter->rotate, 2.f);
	}

	m_2dRenderer->setRenderColour(WHITE);
	for (auto iter = m_bullets.begin(); iter != m_bullets.end(); ++iter) {
		m_2dRenderer->drawSprite(m_bulletTex, iter->pt.x, iter->pt.y, iter->size, iter->size, 0);
	}

	DrawLineBox(BLUE, bounds.pt1.x, bounds.pt1.y, bounds.pt2.x, bounds.pt2.y);

	// loop through the collection of nodes and render everything
	m_2dRenderer->setRenderColour(WHITE);
	for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++) {
		(*iter)->Render(m_2dRenderer);
	}

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", m_cameraX + 10, m_cameraY + 20);
	m_2dRenderer->drawText(m_font, "Press space to change view", m_cameraX + 10, m_cameraY + 60);
	m_2dRenderer->drawText(m_font, "Use WASD to move, hold LFT-Click to shoot", m_cameraX + 10, m_cameraY + 100);
	std::ostringstream os;
	os << " # of bullets: [" << m_bullets.size() << "]";
	m_2dRenderer->drawText(m_font, os.str().c_str(), m_cameraX , m_cameraY + 900);

	// done drawing sprites
	m_2dRenderer->end();
}