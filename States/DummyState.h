#ifndef DUMMYSTATE_H
#define DUMMYSTATE_H

#include <QSGSimpleRectNode>
#include <QElapsedTimer>

#include "State.h"

namespace States
{
	class DummyState : public State
	{
		Q_OBJECT

		Q_PROPERTY(QString fps READ fps NOTIFY fpsChanged)

		public:
			DummyState();

			QString fps() const;

		private:
			QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

			void keyPressEvent(QKeyEvent *event) override;
			void keyReleaseEvent(QKeyEvent *event) override;

			QElapsedTimer m_timer;
			QSGSimpleRectNode *m_node;

			float m_x;
			float m_y;
			float m_direction;
			float m_velocity;
			float m_fpsTimer;
			float m_fps;
			float m_lastFps;

		signals:
			void fpsChanged();
	};
}

#endif // DUMMYSTATE_H
