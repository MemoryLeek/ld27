#ifndef LOGOSTATE_H
#define LOGOSTATE_H

#include "State.h"

namespace States
{
	class LogoState : public State
	{
		Q_OBJECT

		public:
			LogoState();

		private:
			void keyPressEvent(QKeyEvent *) override;

			bool m_skipping;

		private slots:
			void skip();
	};
}

#endif // LOGOSTATE_H
