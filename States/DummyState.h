#ifndef DUMMYSTATE_H
#define DUMMYSTATE_H

#include <QSGSimpleRectNode>
#include <QElapsedTimer>

#include "State.h"
#include "GameState.h"

class Scene;
class Player;
class Bot;

namespace States
{
	class DummyState : public GameState
	{
		Q_OBJECT

		Q_PROPERTY(QString fps READ fps NOTIFY fpsChanged)
		Q_PROPERTY(float timePool READ timePool NOTIFY timePoolChanged)

		public:
			DummyState();

			QString fps() const;
			float timePool() const;

		private:
			void initialize(Scene *scene) override;
			void tick(long delta) override;
			void keyPressed(QKeyEvent *event) override;
			void keyReleased(QKeyEvent *event) override;
			void joystickEvent(const JoystickEvent &event) override;
			void updatePlayerMovement();

			QList<int> m_keyStates;
			JoystickEvent m_lastJoystickEvent;

			Player *m_player;
			QVector<Bot*> m_bots;

			float m_fpsTimer;
			float m_fps;
			float m_lastFps;

			bool m_reverseTime;
			float m_timePool;

		signals:
			void fpsChanged();
			void timePoolChanged();
	};
}

#endif // DUMMYSTATE_H
