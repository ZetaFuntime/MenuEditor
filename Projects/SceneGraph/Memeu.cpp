#include "Memeu.h"
#include <Texture.h>
#include <Renderer2D.h>
#include <Font.h>

Memeu::Memeu()
{

}

Memeu::Memeu(aie::Font *font)
{
	m_font = font;
}

void Memeu::Textin(string input)
{
	m_string = input;
	stringL = m_string.length();
}

Memeu::~Memeu()
{

}

void Memeu::RenderText(aie::Renderer2D *renderer)
{
	renderer->drawText(m_font, m_string.c_str, pos.x, pos.y);
}

void Memeu::SetPos(Vector2 Position)
{
	pos.x = Position.x;
	pos.y = Position.y;
}

Vector2 Memeu::GetPos()
{
	return pos;
}

void Memeu::SetOrigin(const Vector2& origin)
{
	m_origin = origin;
}

const Vector2& Memeu::GetOrigin()
{
	return m_origin;
}