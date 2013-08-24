#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"

class Player : public Actor
{
	public:
		Player(Scene *scene);

		float x() const override;
		float y() const override;

		void tick(const long delta) override;

		void setVelocity(const float velocity);

	private:
		float m_velocity;
		float m_lastVelocity;
		float m_x;
		float m_y;
};

#endif // PLAYER_H
