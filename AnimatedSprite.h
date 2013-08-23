#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <QMovie>

#include "IDrawable.h"

class Scene;

class AnimatedSprite : public IDrawable
{
	public:
		AnimatedSprite(const QString &filename, Scene *scene);

		float x() const override;
		void setX(const float x);

		float y() const override;
		void setY(const float y);

		bool isFlipped();
		void setFlipped(const bool flipped);

		int speed() const;
		void setSpeed(const int speed);

		unsigned int drawingOrder() const override;

		QSGTexture *texture() override;

	private:
		QSGTexture *createTexture(const int frame);

		Scene *m_scene;

		QHash<int, QSGTexture *> m_textures;
		QMovie m_movie;

		float m_x;
		float m_y;

		bool m_flipped;
};

#endif // ANIMATEDSPRITE_H
