#pragma once
#include "Button.h"
#include <vector>

namespace aie
{
	class Font;
}

class MainMenu : public Button
{
public:

	MainMenu();
	virtual ~MainMenu();
	virtual void Update(float deltaTime);
	void Render(aie::Renderer2D * renderer);
	unsigned int StateCheck(Vector2 position, bool input);

	void FormMenu();

	void SetScreenPoints(Vector2 input);

protected:

	Vector2 edgeBorder;

	Button *m_title;
	Button *m_quit;
	Button *m_newgame;
	Button *m_options;

	aie::Font *m_squareFont		= nullptr;
	aie::Font *m_squareFontTitle	= nullptr;

	unsigned int screenWidth;
	unsigned int screenHeight;
	unsigned int titleSize = 60;
	unsigned int normSize = 30;

	std::vector<Button *> m_menu;
};
