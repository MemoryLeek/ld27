#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>

#include <QQuickPaintedItem>
#include <QElapsedTimer>

#include "State.h"
#include "JoystickEvent.h"

class Scene;
class Player;
class Bot;
class SharedState;
class Window;

namespace States
{
	class GameState : public State<QQuickPaintedItem>
	{
		Q_OBJECT

		Q_PROPERTY(QString fps READ fps NOTIFY fpsChanged)
		Q_PROPERTY(float timePool READ timePool NOTIFY timePoolChanged)

		public:
			GameState();

			QString fps() const;
			float timePool() const;

		private:
			void initialize() override;
			void complete() override;

			void paint(QPainter *painter) override;
			void keyPressEvent(QKeyEvent *event) override;
			void keyReleaseEvent(QKeyEvent *event) override;
			void mousePressEvent(QMouseEvent *event) override;
			void mouseReleaseEvent(QMouseEvent *event) override;
			void joystickEvent(const JoystickEvent &event);

			void processJoystick();
			void initializeScene();
			void initializeJoystick();

			JoystickEvent m_lastJoystickEvent;

			Window *m_window;
			Scene *m_scene;
			Player *m_player;
			SDL_Joystick *m_joystick;

			QElapsedTimer m_timer;
			QList<Bot *> m_bots;

			float m_fpsTimer;
			float m_fps;
			float m_lastFps;
			float m_timePool;

			bool m_reverseTime;

		signals:
			void fpsChanged();
			void timePoolChanged();
	};
}

#endif // GAMESTATE_H
