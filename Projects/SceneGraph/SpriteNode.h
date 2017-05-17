
#pragma once

#include "Node.h"

namespace aie
{
	class Texture;
	class Renderer2D;
}

class SpriteNode : public Node
{
public:

	SpriteNode();
	SpriteNode(aie::Texture *texture);
	virtual ~SpriteNode();

	virtual void Render(aie::Renderer2D *renderer);

	void SetSize(const Vector2& size);
	const Vector2& GetSize();

	void SetOrigin(const Vector2& origin);
	const Vector2& GetOrigin();

protected:

	aie::Texture *m_texture = nullptr;
	Vector2 m_size;
	Vector2 m_origin = Vector2(0.5, 0.5);
private:
};
