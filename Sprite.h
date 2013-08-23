#ifndef SPRITE_H
#define SPRITE_H

#include "IDrawable.h"

class Sprite : public IDrawable
{
	public:
		Sprite(const QString &filename, Scene *scene);

		float x() const override;
		void setX(const float x);

		float y() const override;
		void setY(const float y);

		unsigned int drawingOrder() const override;

		QSGTexture *texture() const override;

	private:
		QSGTexture *m_texture;

		float m_x;
		float m_y;
};

#endif // SPRITE_H
