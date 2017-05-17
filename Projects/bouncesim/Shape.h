#pragma once

#include "Node.h"

class SpriteNode;
namespace aie
{
	class Texture;
}

class Shape : public Node
{
public:

	Shape();
	virtual ~Shape();

	virtual void Update(float deltaTime);
	virtual void Render(aie::Renderer2D *renderer);
	//virtual void SetTurretRotate(float p_radians);
	virtual void SetBaseRotate(float p_radians);
	virtual void SetBaseTranslate(Vector2 p_move);
	virtual float GetBaseRotate();

protected:
	SpriteNode *m_ball;
	SpriteNode *m_turret;

	aie::Texture *m_angryTex = nullptr;
	aie::Texture *m_turretTexture = nullptr;

private:
};