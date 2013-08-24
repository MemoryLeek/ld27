#ifndef MUTABLESPRITEBUNDLE_H
#define MUTABLESPRITEBUNDLE_H

#include "shared/SpriteBundle.h"

class MutableSpriteBundle : public SpriteBundle
{
	public:
		MutableSpriteBundle();

		void addSprite(const Sprite sprite);
};

#endif // MUTABLESPRITEBUNDLE_H
