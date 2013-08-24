#ifndef SETTINGSMENUSTATE_H
#define SETTINGSMENUSTATE_H

#include "MenuState.h"

namespace States
{
	class SettingsMenuState : public MenuState
	{
		Q_OBJECT

		public:
			SettingsMenuState();

			QList<QObject *> entries() override;

		private:
			QList<QObject *> m_entries;
	};
}

#endif // SETTINGSMENUSTATE_H
