#include "Sprite.h"
#include "Scene.h"

Sprite::Sprite(const QString &filename, Scene *scene)
	 : IDrawable(scene)
{
	m_texture = scene->createTexture(filename);
	m_x = 0;
	m_y = 0;
}

float Sprite::x() const
{
	return m_x;
}

void Sprite::setX(const float x)
{
	m_x = x;
}

float Sprite::y() const
{
	return m_y;
}

void Sprite::setY(const float y)
{
	m_y = y;
}

unsigned int Sprite::drawingOrder() const
{
	return 0;
}

QSGTexture *Sprite::texture() const
{
	return m_texture;
}
