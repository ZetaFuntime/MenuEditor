#pragma once

#include "Node.h"
#include <vector>

namespace aie
{
	class Texture;
	class Renderer2D;
}

class Hitbox : public Node
{
public:

	Hitbox();
	Hitbox(aie::Texture *texture);
	virtual ~Hitbox();

	virtual void Render(aie::Renderer2D *renderer);

	// Return functions for each corner of the hitbox
	Vector2 Return_posTL();
	Vector2 Return_posTR();
	Vector2 Return_posBL();
	Vector2 Return_posBR();

	void SetSize(const Vector2& size);
	const Vector2& GetSize();

	void SetOrigin(const Vector2& origin);
	const Vector2& GetOrigin();

protected:

	aie::Texture *m_texture = nullptr;
	Vector2 m_size;
	Vector2 m_origin = Vector2(0.5, 0.5);

	// Positions for each corner of the hitbox
	Vector2 posTL;				
	Vector2 posTR;
	Vector2 posBL;
	Vector2 posBR;

private:
};