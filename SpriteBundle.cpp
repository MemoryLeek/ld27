#include <QImage>
#include <QFile>

#include "SpriteBundle.h"

SpriteBundle::SpriteBundle()
{
	m_index = 0;
}

void SpriteBundle::update(const int delta)
{
	Sprite &image = m_sprites[m_index];
	image.update(delta);
}

void SpriteBundle::setImageIndex(const int index)
{
	m_index = index;
}

QImage SpriteBundle::currentImage(bool flipped) const
{
	const Sprite &image = m_sprites[m_index];
	const QImage &frame = image.currentFrame(flipped);

	return frame;
}

int SpriteBundle::spriteCount() const
{
	return m_sprites.count();
}

int SpriteBundle::imageIndex() const
{
	return m_index;
}

QDataStream &operator >>(QDataStream &stream, SpriteBundle &bundle)
{
	stream >> bundle.m_sprites;

	return stream;
}
