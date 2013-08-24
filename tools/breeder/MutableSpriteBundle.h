#ifndef MUTABLESPRITEBUNDLE_H
#define MUTABLESPRITEBUNDLE_H

#include "MutableSprite.h"

class MutableSpriteBundle
{
	public:
		MutableSpriteBundle();

		void addSprite(const MutableSprite sprite);

	private:
		friend QDataStream &operator <<(QDataStream &stream, const MutableSpriteBundle &bundle);

		QList<MutableSprite> m_sprites;
};

#endif // MUTABLESPRITEBUNDLE_H
