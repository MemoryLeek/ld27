#ifndef LOGOSTATE_H
#define LOGOSTATE_H

#include "State.h"

namespace States
{
	class LogoState : public State<QQuickItem>
	{
		Q_OBJECT

		public:
			LogoState();

		private:
			void initialize() override;
			void complete() override;
			void timerEvent(QTimerEvent *) override;
			void keyPressEvent(QKeyEvent *) override;

			bool m_skipping;
			int m_timerId;

		private slots:
			void skip();
	};
}

#endif // LOGOSTATE_H
