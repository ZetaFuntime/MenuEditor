#pragma once

#include "Node.h"

class SpriteNode;
class Hitbox;

namespace aie
{
	class Texture;
}

class Tank : public Node
{
public:

	Tank();
	virtual ~Tank();

	void SetBoundCenter(Vector2 bounds);

	Vector2 GetGlobalCameraPos();
	Vector2 GetLocalCameraPos();
	bool CameraState();
	void SwitchCamera();

	virtual void Update(float deltaTime);
	virtual void Render(aie::Renderer2D *renderer);
	virtual void SetTurretRotate(float p_radians);
	virtual void SetBaseRotate(float p_radians);
	
	virtual void SetBaseTranslate(Vector2 p_move);
	virtual float GetBaseRotate();

protected:

	bool Cameralock;
	Node *m_camera;
	Node *m_bounds;
	SpriteNode *m_base;
	SpriteNode *m_turret;
	SpriteNode *m_bullet;
	Hitbox *baseBox;

	aie::Texture *m_tankBaseTexture = nullptr;
	aie::Texture *m_turretTexture	= nullptr;
	aie::Texture *m_bulletTexture	= nullptr;

private:
};