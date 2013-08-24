#ifndef ACTOR_H
#define ACTOR_H

#include "IDrawable.h"
#include "SpriteBundle.h"

class Actor : public IDrawable
{
	public:
		Actor(const QString &filename, Scene *scene);

		unsigned int drawingOrder() const override;

		QSGTexture *texture() override;

		virtual void tick(const long delta) = 0;

	protected:
		enum ImageStates
		{
			Idle,
			Walking,
			Jumping,
			Falling
		};

		SpriteBundle m_sprite;
		bool m_flipped;

	private:
		Scene *m_scene;
};

#endif // ACTOR_H
