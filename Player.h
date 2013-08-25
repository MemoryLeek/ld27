#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"

class Map;

class Player : public Actor
{
	public:
		Player(Map *map, Scene *scene);

		float x() const override;
		float y() const override;

		void tick(const long delta) override;

		void setVelocity(const float velocity);
		void setDirection(const float direction);
		void jump();

	private:
		enum ImageStates
		{
			Idle,
			Walking,
			Jumping,
			Falling,
			Clinging
		};

		float m_xVelocity;
		float m_yVelocity;
		float m_xThrust;
		float m_yThrust;
		float m_lastDirection;

		float m_x;
		float m_y;

		bool m_isOnGround;

		Map *m_map;
};

#endif // PLAYER_H
