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

		QSGTexture *currentFrame(Scene *scene, const bool flipped);

		float delay() const;
		int frameCount() const;

	private:
		QSGTexture *createTexture(Scene *scene, const int index, const bool flipped);

		friend QDataStream &operator >>(QDataStream &stream, Sprite &sprite);

		QList<QImage> m_frames;
		QHash<int, QSGTexture *> m_textures;

		float m_delay;
		float m_index;
};

#endif // SPRITE_H
