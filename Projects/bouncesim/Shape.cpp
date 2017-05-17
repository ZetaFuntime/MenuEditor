#include "Shape.h"
#include <Texture.h>
#include "SpriteNode.h"
#include "Input.h"

Shape::Shape()
{
	//Put the textures here
	m_angryTex = new aie::Texture("./textures/angery.png");
	//m_turretTexture = new aie::Texture("./sceneGraph/textures/barrelGreen.png");

	//m_turret = new SpriteNode(m_turretTexture);
	//m_turret->Translate(Vector2(0, 0));
	//m_turret->SetOrigin(Vector2(0.0f, 0.5f));

	// Circle Texture + Node rotation
	m_ball = new SpriteNode(m_angryTex);
	m_ball->Rotate(3.14159f / 4.0f); // 90 degrees

	//Parent setups
	//m_turret->SetParent(m_base);
	//m_base->SetParent(this);
}

Shape::~Shape()
{
	delete m_ball;

	delete m_angryTex;
}

void Shape::Update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
}

void Shape::Render(aie::Renderer2D *renderer)
{
	m_ball->Render(renderer);
	m_turret->Render(renderer);
}

//void Shape::SetTurretRotate(float p_radians)
//{
//	float bRads = m_base->GetLocalRotation();
//	m_turret->setLocalMatrix(p_radians - bRads);
//}

void Shape::SetBaseRotate(float p_radians)
{
	m_ball->setLocalMatrix(p_radians);
}

void Shape::SetBaseTranslate(Vector2 p_move)
{
	m_ball->Translate(p_move);
}

float Shape::GetBaseRotate()
{
	return m_ball->GetLocalRotation();
}