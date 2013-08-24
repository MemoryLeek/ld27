#ifndef DUMMYSTATE_H
#define DUMMYSTATE_H

#include <QSGSimpleRectNode>
#include <QElapsedTimer>

#include "State.h"
#include "GameState.h"

class Scene;
class Player;

namespace States
{
	class DummyState : public GameState
	{
		Q_OBJECT

		Q_PROPERTY(QString fps READ fps NOTIFY fpsChanged)

		public:
			DummyState();

			QString fps() const;

		private:
			void initialize(Scene *scene) override;
			void tick(long delta) override;
			void keyPressed(QKeyEvent *event) override;
			void keyReleased(QKeyEvent *event) override;
			void updatePlayerMovement();

			QList<int> m_keyStates;

			Player *m_player;

			float m_fpsTimer;
			float m_fps;
			float m_lastFps;

		signals:
			void fpsChanged();
	};
}

#endif // DUMMYSTATE_H
