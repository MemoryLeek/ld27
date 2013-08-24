#ifndef MUTABLESPRITE_H
#define MUTABLESPRITE_H

#include "shared/Sprite.h"

class MutableSprite : public Sprite
{
	public:
		void addFrame(const QImage image);
		void setDelay(const float delay);

		bool isValid() const;
};

#endif // MUTABLESPRITE_H
