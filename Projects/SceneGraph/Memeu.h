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

class Memeu
{
public:
	Memeu();
	Memeu(aie::Font *font);
	void Textin(string input);
	virtual ~Memeu();

	virtual void RenderText(aie::Renderer2D * renderer);

	void SetPos(Vector2 Position);
	Vector2 GetPos();

	void SetOrigin(const Vector2 & origin);
	const Vector2& GetOrigin();

protected:
	
	aie::Font *m_font = nullptr;
	Vector2 pos;
	string m_string;
	int stringL;
	Vector2 m_origin = Vector2(0.5, 0.5);
};

