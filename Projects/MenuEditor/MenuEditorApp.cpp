#define _USE_MATH_DEFINES
#include "MenuEditorApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Utility.h>
#include <math.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "MainMenu.h"

MenuEditorApp::MenuEditorApp() {

}

MenuEditorApp::~MenuEditorApp() {

}

bool MenuEditorApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_text = new aie::Font("./font/SquareBoldsFree.ttf",20);

	m_menu = new MainMenu();
	m_menu->SetScreenPoints(Vector2(getWindowWidth(), getWindowHeight()));
	m_menu->FormMenu();
	return true;
}

void MenuEditorApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void MenuEditorApp::update(float deltaTime) {

	unsigned int state;
	// input example
	aie::Input* input = aie::Input::getInstance();

	// grab mouse coords
	mouseX, mouseY;
	input->getMouseXY(&mouseX, &mouseY);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	state = m_menu->StateCheck(Vector2(mouseX, mouseY),input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT));

	std::cout << "State is:" << state << " ." << std::endl;
	m_menu->Update(deltaTime);
}

void MenuEditorApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	
	// output some text, uses the last used colour
	m_2dRenderer->setRenderColour(WHITE);
	std::ostringstream os;
	os << "Coords:[" << mouseX << "][" << mouseY << "]";
	m_2dRenderer->drawText(m_font, os.str().c_str(), 0, 0);

	// Render the menu
	m_menu->Render(m_2dRenderer);
	// done drawing sprites
	m_2dRenderer->end();
}