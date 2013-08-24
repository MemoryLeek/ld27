#include "MutableSpriteBundle.h"

MutableSpriteBundle::MutableSpriteBundle()
{

}

void MutableSpriteBundle::addSprite(const MutableSprite sprite)
{
	m_sprites << sprite;
}

QDataStream &operator <<(QDataStream &stream, const MutableSpriteBundle &bundle)
{
	stream << bundle.m_sprites;

	return stream;
}
