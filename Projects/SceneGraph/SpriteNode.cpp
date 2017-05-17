#include "SpriteNode.h"
#include <Texture.h>
#include <Renderer2D.h>

SpriteNode::SpriteNode()
{

}

SpriteNode::SpriteNode(aie::Texture *texture)
{
	m_texture = texture;
	m_size.x = (float)m_texture->getWidth();
	m_size.y = (float)m_texture->getHeight();
}

SpriteNode::~SpriteNode()
{

}

void SpriteNode::Render(aie::Renderer2D *renderer)
{
	Matrix3 gTransform = CalculateGlobalTransform();

	Vector2 pos = gTransform.getTranslation();
	Vector2 scale(gTransform[0].magnitude(), gTransform[1].magnitude());
	float rot = gTransform.getRotationZ();

	renderer->drawSprite(
		m_texture, 
		pos.x, pos.y, 
		scale.x*m_size.x, scale.y*m_size.y, 
		rot, 
		0,
		m_origin.x, m_origin.y
	);
}

void SpriteNode::SetSize(const Vector2& size)
{
	m_size = size;
}

const Vector2& SpriteNode::GetSize()
{
	return m_size;
}

void SpriteNode::SetOrigin(const Vector2& origin)
{
	m_origin = origin;
}
const Vector2& SpriteNode::GetOrigin()
{
	return m_origin;
}