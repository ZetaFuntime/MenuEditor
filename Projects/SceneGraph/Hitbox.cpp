#include "Hitbox.h"
#include <Texture.h>
#include <Renderer2D.h>

Hitbox::Hitbox()
{

}

Hitbox::Hitbox(aie::Texture *texture)
{
	m_texture = texture;
	m_size.x = (float)m_texture->getWidth();
	m_size.y = (float)m_texture->getHeight();

}

Hitbox::~Hitbox()
{

}

void Hitbox::Render(aie::Renderer2D *renderer)
{
	Matrix3 gTransform = CalculateGlobalTransform();
	Vector2 pos = gTransform.getTranslation();
	Vector2 scale(gTransform[0].magnitude()*2, gTransform[1].magnitude()*2);
	Vector2 dist = Vector2(m_size.x / 2, m_size.y / 2);
	float radO = 3.14159f;
	float rot = gTransform.getRotationZ();

	// Calculate the corners of the node
	posTL = Vector2(pos.x + cos(rot + radO*0.25f)*scale.x*dist.x, pos.y + sin(rot + radO*0.25f)*scale.y*dist.y);
	renderer->drawCircle(posTL.x, posTL.y, 2.5f);

	posTR = Vector2(pos.x + cos(rot - radO*0.25f)*scale.x*dist.x, pos.y + sin(rot - radO*0.25f)*scale.y*dist.y);
	renderer->drawCircle(posTR.x, posTR.y, 2.5f);

	posBL = Vector2(pos.x - cos(-rot + radO*0.25f)*scale.x*dist.x, pos.y + sin(-rot + radO*0.25f)*scale.y*dist.y);	
	renderer->drawCircle(posBL.x, posBL.y, 2.5f);

	Vector2 posBR = Vector2(pos.x - cos(-rot - radO*0.25f)*scale.x*dist.x, pos.y + sin(-rot - radO*0.25f)*scale.y*dist.y);
	renderer->drawCircle(posBR.x, posBR.y, 2.5f);

	// Draw the hitbox - assuming "forwards" is the top
	renderer->drawLine(posTL.x, posTL.y, posTR.x, posTR.y);			// Top side
	renderer->drawLine(posBL.x, posBL.y, posTL.x, posTL.y);			// Left Side
	renderer->drawLine(posBL.x, posBL.y, posBR.x, posBR.y);			// Bottom Side
	renderer->drawLine(posTR.x, posTR.y, posBR.x, posBR.y);			// Right Side
	renderer->drawLine(posTL.x, posTL.y, posBR.x, posBR.y);			// TL to BR
	renderer->drawLine(posBL.x, posBL.y, posTR.x, posTR.y);			// TR to BL

}

Vector2 Hitbox::Return_posTL()
{
	return posTL;
}

Vector2 Hitbox::Return_posTR()
{
	return posTR;
}

Vector2 Hitbox::Return_posBL()
{
	return posBL;
}

Vector2 Hitbox::Return_posBR()
{
	return posBR;
}

void Hitbox::SetSize(const Vector2& size)
{
	m_size = size;
}

const Vector2& Hitbox::GetSize()
{
	return m_size;
}

void Hitbox::SetOrigin(const Vector2& origin)
{
	m_origin = origin;
}
const Vector2& Hitbox::GetOrigin()
{
	return m_origin;
}