#ifndef DEATHSTATE_H
#define DEATHSTATE_H

#include <QQuickItem>

#include "MenuState.h"

class StateHandler;

namespace States
{
	class DeathState : public MenuState
	{
		Q_OBJECT

		public:
			DeathState();

			QList<QObject *> entries() override;

		private:
			void retry();
			void quit();

			void initialize() override;
			void complete() override;

			StateHandler *m_stateHandler;

			QList<QObject *> m_entries;
	};
}

#endif // DEATHSTATE_H
