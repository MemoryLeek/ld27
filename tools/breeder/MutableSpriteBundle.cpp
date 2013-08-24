#include "MutableSpriteBundle.h"

MutableSpriteBundle::MutableSpriteBundle()
{

}

void MutableSpriteBundle::addSprite(const Sprite sprite)
{
	m_sprites << sprite;
}
