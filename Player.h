#ifndef PLAYER_H
#define PLAYER_H

//#include <QSoundEffect>

#include "Actor.h"

class Map;
class Window;
class SharedState;

class Player : public Actor
{
	public:
		Player(Map *map, Scene *scene, Window *window);

		float x() const override;
		float y() const override;

		void tick(const long delta) override;

		void setVelocity(const float velocity);
		void setDirection(const float direction);
		void jump();
		void respawn();

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
		Window *m_window;

//		QSoundEffect m_jumpSound;
//		QSoundEffect m_stepSound;
//		long m_stepSoundTimer;
};

#endif // PLAYER_H
