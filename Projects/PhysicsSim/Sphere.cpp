#include "Sphere.h"
#include <Texture.h>
#include "../SceneGraph/SpriteNode.h"
#include "Input.h"

Sphere::Sphere()
{
	m_sphereTex = new aie::Texture("./sceneGraph/textures/tankBlue.png");

	m_sphere = new SpriteNode(m_sphereTex);
}

Sphere::~Sphere()
{
	delete m_sphere;

	delete m_sphereTex;
}

void Sphere::Update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
}

void Sphere::Render(aie::Renderer2D *renderer)
{
	m_sphere->Render(renderer);
}

void Sphere::SetBaseRotate(float p_radians)
{
	m_sphere->setLocalMatrix(p_radians);
}

void Sphere::SetBaseTranslate(Vector2 p_move)
{
	m_sphere->Translate(p_move);
}

float Sphere::GetBaseRotate()
{
	return m_sphere->GetLocalRotation();
}