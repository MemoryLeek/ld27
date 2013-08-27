#ifndef SPRITE_H
#define SPRITE_H

#include <QImage>
#include <QDataStream>
#include <QSGTexture>
#include <QHash>

class Scene;

class Sprite
{
	public:
		Sprite();

		void update(const int delta);

		QImage currentFrame(const bool flipped) const;

		float delay() const;
		int frameCount() const;

	private:
		friend QDataStream &operator >>(QDataStream &stream, Sprite &sprite);

		QList<QImage> m_frames;

		float m_delay;
		float m_index;
};

#endif // SPRITE_H
