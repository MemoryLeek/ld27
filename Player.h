#ifndef PLAYER_H
#define PLAYER_H

#include <QSoundEffect>

#include "SpriteBundle.h"
#include "IDrawable.h"

class Map;
class StateHandler;
class SharedState;

class Player : public IDrawable
{
	public:
		Player(Map *map, StateHandler *stateHandler);

		float x() const;
		float y() const;

		int width() const;
		int height() const;

		unsigned int drawingOrder() const;

		void draw(FrameDrawingContext &context, const int cx, const int cy, const int delta) override;

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
		bool m_flipped;

		Map *m_map;
		StateHandler *m_stateHandler;
		SpriteBundle m_sprite;

//		QSoundEffect m_jumpSound;
//		QSoundEffect m_stepSound;
		long m_stepSoundTimer;
};

#endif // PLAYER_H
