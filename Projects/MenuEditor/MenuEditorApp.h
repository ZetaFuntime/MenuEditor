#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <vector>

class MainMenu;
class Button;

class MenuEditorApp : public aie::Application {
public:

	MenuEditorApp();
	virtual ~MenuEditorApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	int mouseX, mouseY;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	aie::Font*			m_text;

	MainMenu *m_menu = nullptr;

};