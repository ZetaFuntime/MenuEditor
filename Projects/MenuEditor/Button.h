#pragma once
#pragma once
#include "Matrix3.h"
#include "Vector2.h"
#include <iostream>
#include <string.h>

using std::string;

namespace aie
{
	class Font;
	class Renderer2D;
}

// Colour Palette
enum Colors {
	RED		= 0xff0000ff, DK_RED	 = 0x800000ff,
	YELLOW	= 0xffff00ff, DK_YELLOW	 = 0x999900ff,
	ORANGE	= 0xff8000ff, DK_ORANGE	 = 0x994C00ff,
	GREY	= 0xC0C0C0ff, DK_GREY	 = 0x808080ff,
	GREEN	= 0x00ff00ff, DK_GREEN	 = 0x009900ff,
	TEAL	= 0x00ffffff, DK_TEAL	 = 0x009999ff, 
	BLUE	= 0x0000ffff, DK_BLUE	 = 0x000099ff, 
	PURPLE	= 0x7f00ffff, DK_PURPLE	 = 0x4C0099ff,
	MAGENTA = 0xff00ffff, DK_MAGENTA = 0x990099ff,
	LIME	= 0x80ff00ff, DK_LIME	 = 0x4C9900ff,
	WHITE	= 0xffffffff, BLACK		 = 0x000000ff
};

class Button
{
public:
	Button();
	Button(aie::Font *font, unsigned int textSize);
	void Textin(string input);
	int GetStringLength();
	virtual ~Button();
	virtual void Render(aie::Renderer2D * renderer);

	void SetPos(Vector2 Position);
	void SetSpacing(Vector2 spacing);
	Vector2 GetPos();

	unsigned int GetTextSize();
	bool HoverCheck(Vector2 position, bool input);
	void SetTextSize(unsigned int size);
	void HoverCheck(Vector2 position);

	bool IdentityCheck();

	void IdentityButton();
	void IdentityText();

	void SetBoxColour(Colors input);
	void SetTextColour(Colors input);

private:

	Colors DarkenColour();
	Colors LightenColour();

protected:

	// Point parameters for the "box" of the button 
	Vector2 pt1;
	Vector2 pt2;
	Vector2 pt3;
	Vector2 pt4;

	bool isButton;
	bool isText;
	bool inside;
	aie::Font *m_font = nullptr;
	Colors textColour;
	Colors boxColour;
	Vector2 pos;
	Vector2 boxspacing = Vector2(30, 10);
	string m_string;
	unsigned int m_size;
};

