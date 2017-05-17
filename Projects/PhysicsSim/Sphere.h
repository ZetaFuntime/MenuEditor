#pragma once
#include "..\SceneGraph\Node.h"

class SpriteNode;
namespace aie
{
	class Texture;
}

class Sphere : public Node
{
public:

	Sphere();
	virtual ~Sphere();

	virtual void Update(float deltaTime);
	virtual void Render(aie::Renderer2D *renderer);
	virtual void SetBaseRotate(float p_radians);
	virtual void SetBaseTranslate(Vector2 p_move);
	virtual float GetBaseRotate();

protected:
	SpriteNode *m_sphere;

	aie::Texture *m_sphereTex = nullptr;
};
