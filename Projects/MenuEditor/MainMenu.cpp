#include "MainMenu.h"
#include <Font.h>
#include <Application.h>
#include "Input.h"
#include <assert.h>
#include <iostream>

MainMenu::MainMenu()
{
	m_squareFontTitle = new aie::Font("./Font/SquaresBoldFree.ttf", titleSize);
	m_squareFont = new aie::Font("./Font/SquaresBoldFree.ttf", normSize);

	m_title = new Button(m_squareFontTitle, titleSize);
	m_title->SetTextColour(WHITE);
	m_title->Textin("MenuMaker 2017");
	m_title->IdentityText();
	m_menu.push_back(m_title);

	m_newgame = new Button(m_squareFont, normSize);
	m_newgame->SetBoxColour(DK_GREEN);
	m_newgame->Textin("Play Game");
	m_newgame->IdentityButton();
	m_menu.push_back(m_newgame);

	m_options = new Button(m_squareFont, normSize);
	m_options->SetBoxColour(DK_BLUE);
	m_options->Textin("Options");
	m_options->IdentityButton();
	m_menu.push_back(m_options);

	m_quit = new Button(m_squareFont, normSize);
	m_quit->SetBoxColour(DK_RED);
	m_quit->Textin("Quit");
	m_quit->IdentityButton();
	m_menu.push_back(m_quit);
}

MainMenu::~MainMenu()
{
	delete m_squareFontTitle;
	delete m_squareFont;
	
	delete m_title;
	delete m_newgame;
	delete m_quit;
	delete m_options;
}

void MainMenu::Update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
}

void MainMenu::Render(aie::Renderer2D *renderer)
{
	for (unsigned int i = 0; i < m_menu.size(); i++){
		m_menu[i]->Render(renderer);
	}
}

unsigned int MainMenu::StateCheck(Vector2 position, bool input)
{
	for (unsigned int i = 0; i < m_menu.size(); i++) {
		if (m_menu[i]->IdentityCheck()) {
			if(m_menu[i]->HoverCheck(position, input)) return i;
		}
	}
}

void MainMenu::FormMenu()
{
	edgeBorder = Vector2(50, 50);
	unsigned int menuSpacing = (screenHeight - edgeBorder.y*2) / m_menu.size();
	unsigned int menuTop = menuSpacing*m_menu.size();
	unsigned int menuCenter = (screenWidth / 2);
	for (unsigned int i = 0; i < m_menu.size(); i++)
	
	{
		// - ((int)m_menu[i]->GetStringLength()*(int)m_menu[i]->GetTextSize());
		m_menu[i]->SetPos(Vector2(menuCenter, menuTop));
		std::cout << "Menu pos: " << menuCenter << " " << menuTop << std::endl;
		menuTop -= menuSpacing;
		m_menu[i]->SetSpacing(Vector2(m_menu[i]->GetTextSize() / 4, m_menu[i]->GetTextSize() / 4));
	}
}

void MainMenu::SetScreenPoints(Vector2 input)
{
	if(input.x < 0 || input.y < 0)std::cout << "This is too small!";
	screenHeight = input.y;
	screenWidth = input.x;
}