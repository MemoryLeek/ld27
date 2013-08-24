#include "Actor.h"
#include "SpriteLoader.h"

Actor::Actor(const QString &filename, Scene *scene)
	: IDrawable(scene)
{
	SpriteLoader spriteLoader;
	SpriteBundle sprite = spriteLoader.load(filename);

	m_sprite = sprite;
	m_scene = scene;
	m_x = 0;
	m_y = 0;
	m_velocity = 0;
	m_lastVelocity = 0;
	m_flipped = false;
}

float Actor::x() const
{
	return m_x;
}

float Actor::y() const
{
	return m_y;
}

unsigned int Actor::drawingOrder() const
{
	return 0;
}

QSGTexture *Actor::texture()
{
	return m_sprite.currentImage(m_scene, m_flipped);
}

void Actor::tick(const long delta)
{
	m_sprite.update(delta);
	m_x += m_velocity * (delta / 1000.0f);
}

void Actor::setVelocity(const float velocity)
{
	m_velocity = velocity;

	if(m_velocity != 0)
	{
		m_sprite.setImageIndex(Walking);
		m_flipped = m_velocity < 0 || (!m_velocity && m_lastVelocity < 0);
		m_lastVelocity = m_velocity;
	}
	else
	{
		m_sprite.setImageIndex(Idle);
	}
}
