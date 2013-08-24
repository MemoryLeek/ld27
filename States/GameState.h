#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QElapsedTimer>

#include <SDL2/SDL_joystick.h>

#include "JoystickEvent.h"

#include "State.h"

class Scene;

namespace States
{
	class GameState : public State
	{
		public:
			GameState();
			~GameState();

		protected:
			virtual void initialize(Scene *scene) = 0;
			virtual void tick(long delta) = 0;
			virtual void keyPressed(QKeyEvent *event) = 0;
			virtual void keyReleased(QKeyEvent *event) = 0;
			virtual void joystickEvent(const JoystickEvent &event) = 0;

		private:
			QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

			void keyPressEvent(QKeyEvent *event) override;
			void keyReleaseEvent(QKeyEvent *event) override;

			QElapsedTimer m_timer;
			Scene *m_scene;

			SDL_Joystick *m_joystick;
			JoystickEvent m_lastJoystickEvent;
	};
}

#endif // GAMESTATE_H
