#ifndef SPRITEBUNDLE_H
#define SPRITEBUNDLE_H

#include <QString>
#include <QList>
#include <QDataStream>
#include <QSGTexture>

#include "Sprite.h"

class Scene;

class SpriteBundle
{
	public:
		SpriteBundle();

		void update(const int delta);
		void setImageIndex(const int index);

		QSGTexture *currentImage(Scene *scene, bool flipped);

		int spriteCount() const;
		int imageIndex() const;

	protected:
		QList<Sprite> m_sprites;

	private:
		friend QDataStream &operator >>(QDataStream &stream, SpriteBundle &bundle);

		int m_index;
};

#endif // SPRITEBUNDLE_H
