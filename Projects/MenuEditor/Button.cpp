#include "Button.h"
#include <Texture.h>
#include <Renderer2D.h>
#include <Font.h>
#include <iostream>

Button::Button()
{
	textColour = WHITE;
	boxColour = WHITE;
}

Button::Button(aie::Font *font, unsigned int textSize)
{
	m_font = font;
	m_size = textSize;
}

void Button::Textin(string input)
{
	string temp = input;
	(temp.length() > 50 && !(isButton)) ? m_string = "Insert memes instead mayn": m_string = input;
	std::cout << "String length is: " << m_string.length();
}

int Button::GetStringLength()
{
	return m_string.length();
}

Button::~Button()
{

}

Colors Button::DarkenColour()
{
	bool success = false;
	switch (boxColour){
	case RED	:	boxColour = DK_RED;		success = true; break;
	case YELLOW	:	boxColour = DK_YELLOW;	success = true; break;
	case ORANGE	:	boxColour = DK_ORANGE;	success = true; break;
	case GREY	:	boxColour = DK_GREY;	success = true; break;
	case GREEN	:	boxColour = DK_GREEN;	success = true; break;
	case BLUE	:	boxColour = DK_BLUE;	success = true; break;
	case PURPLE	:	boxColour = DK_PURPLE;	success = true; break;
	case LIME	:	boxColour = DK_LIME;	success = true; break;
	case TEAL	:	boxColour = DK_TEAL;	success = true; break;
	case MAGENTA:	boxColour = DK_MAGENTA;	success = true; break;
	default: break;
	}
	if (success) std::cout << "Colour switched - Darker." << std::endl;
	return boxColour;
}

Colors Button::LightenColour()
{
	bool success = false;
	switch (boxColour) {
	case DK_RED:		boxColour = RED;	 success = true; break;
	case DK_YELLOW:		boxColour = YELLOW;	 success = true; break;
	case DK_ORANGE:		boxColour = ORANGE;	 success = true; break;
	case DK_GREY:		boxColour = GREY;	 success = true; break;
	case DK_GREEN:		boxColour = GREEN;	 success = true; break;
	case DK_BLUE:		boxColour = BLUE;	 success = true; break;
	case DK_PURPLE:		boxColour = PURPLE;	 success = true; break;
	case DK_LIME:		boxColour = LIME;	 success = true; break;
	case DK_TEAL:		boxColour = TEAL;	 success = true; break;
	case DK_MAGENTA:	boxColour = MAGENTA; success = true; break;
	default: break;
	}
	if (success) std::cout << "Colour switched - Lighter." << std::endl;
	return boxColour;
}

void Button::Render(aie::Renderer2D *renderer)
{
	if (isButton) {
		renderer->setRenderColour((inside) ? LightenColour() : DarkenColour());
		renderer->drawLine(pt1.x, pt1.y, pt2.x, pt2.y);		// Left Side
		renderer->drawLine(pt2.x, pt2.y, pt3.x, pt3.y);		// Top Side
		renderer->drawLine(pt3.x, pt3.y, pt4.x, pt4.y);		// Right Side
		renderer->drawLine(pt4.x, pt4.y, pt1.x, pt1.y);		// Bottom Side
		float textBegin = pos.x - (m_string.length()*m_size / 3);
		renderer->drawText(m_font, m_string.c_str(), textBegin, pos.y);

	} if (isText) {
		renderer->setRenderColour(textColour);\
			float textBegin = pos.x - (m_string.length()*m_size/3);
		renderer->drawText(m_font, m_string.c_str(), textBegin, pos.y);
	}
}

void Button::SetPos(Vector2 Position)
{
	pos.x = Position.x;
	pos.y = Position.y;

	if (isButton) {
		pt1 = Vector2((float)pos.x - ((m_string.length()*m_size /3)) - boxspacing.x, (float)pos.y - boxspacing.y);				// Calculate bottom left of the box
		pt3 = Vector2((float)pos.x + ((m_string.length()*m_size /3)) + boxspacing.x, (float)pos.y + m_size);		// Calculate top right of the box
		pt2 = Vector2((float)pt1.x, (float)pt3.y);																				// Calculate top left of the box
		pt4 = Vector2((float)pt3.x, (float)pt1.y);																				// Calculate bottom right of the box
		if (pt3.x - pt1.x < 50 ){
			pt3.x = pos.x - 25 - boxspacing.x;
			pt1.x = pos.x + 25 + boxspacing.x;
			pt4.x = pt3.x;
			pt2.x = pt1.x;
		}
	}
}

void Button::SetSpacing(Vector2 spacing)
{
	boxspacing = spacing;
}

Vector2 Button::GetPos()
{
	return pos;
}

void Button::SetBoxColour(Colors input)
{
	boxColour = input;
}

void Button::SetTextColour(Colors input)
{
	textColour = input;
}

void Button::SetTextSize(unsigned int size)
{
	m_size = size;
}

unsigned int Button::GetTextSize()
{
	return m_size;
}

bool Button::HoverCheck(Vector2 position, bool input)
{
	bool output = false;
	((position.x >= pt1.x && position.x <= pt3.x) && (position.y >= pt1.y && position.y <= pt3.y))? inside = true : inside = false;
	if (input && inside) output = true;
	return output;
}

bool Button::IdentityCheck()
{
	return isButton;
}

void Button::IdentityButton()
{
	isButton = true;
	isText = false;
}

void Button::IdentityText()
{
	isText = true;
	isButton = false;
}
