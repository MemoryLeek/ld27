#ifndef ACTOR_H
#define ACTOR_H

#include "IDrawable.h"
#include "SpriteBundle.h"

class Actor : public IDrawable
{
	public:
		Actor(const QString &filename, Scene *scene);

		float x() const override;
		float y() const override;

		unsigned int drawingOrder() const override;

		QSGTexture *texture() override;

		void tick(const long delta);
		void setVelocity(const float velocity);

	private:
		enum ImageStates
		{
			Idle,
			Walking,
			Jumping,
			Falling
		};

		SpriteBundle m_sprite;
		Scene *m_scene;

		float m_velocity;
		float m_lastVelocity;
		float m_x;
		float m_y;

		bool m_flipped;
};

#endif // ACTOR_H
