#include "Actor.h"
#include "SpriteLoader.h"

Actor::Actor(const QString &filename, Scene *scene)
	: IDrawable(scene)
{
	SpriteLoader spriteLoader;
	SpriteBundle sprite = spriteLoader.load(filename);

	m_sprite = sprite;
	m_scene = scene;
	m_flipped = false;
}

unsigned int Actor::drawingOrder() const
{
	return 0;
}

QSGTexture *Actor::texture()
{
	return m_sprite.currentImage(m_scene, m_flipped);
}
