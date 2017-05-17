#include "Node.h"
#include <Renderer2D.h>

Node::Node()
{

}

Node::~Node()
{

}

void Node::Update(float dt)
{

}

void Node::Render(aie::Renderer2D *renderer)
{
	// DEBUG RENDERING
	// TODO: Put condition in to toggle debug rendering for basic nodes
	Matrix3 gTransform = CalculateGlobalTransform();
	Vector2 pos = gTransform.getTranslation();
	float rot = gTransform.getRotationZ();

	renderer->drawBox(pos.x, pos.y, 10, 20, rot);
}

void Node::SetParent(Node *parent)
{
	m_parent = parent;
}

Matrix3& Node::GetTransform()
{
	return m_local;
}

Matrix3 Node::CalculateGlobalTransform() const
{
	if (m_parent == nullptr)
		return m_local;

	return m_parent->CalculateGlobalTransform() * m_local;
}

void Node::Translate(const Vector2 &pos)
{
	Matrix3 translation = Matrix3::createTranslation(pos.x, pos.y);
	m_local = m_local * translation;
}

void Node::Rotate(float radians)
{
	Matrix3 rotation = Matrix3::createRotation(radians);
	m_local = m_local * rotation;
}

Vector2 Node::GetLocalPosition()
{
	return m_local.getTranslation();
}
float Node::GetLocalRotation()
{
	return m_local.getRotationZ();
}


Vector2 Node::GetGlobalPosition()
{
	return CalculateGlobalTransform().getTranslation();
}
float Node::GetGlobalRotation()
{
	return CalculateGlobalTransform().getRotationZ();
}