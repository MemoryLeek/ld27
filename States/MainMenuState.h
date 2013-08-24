#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "MenuState.h"

namespace States
{
	class MainMenuState : public MenuState
	{
		public:
			MainMenuState();

			QList<QObject *> entries() override;

		private:
			void start();
			void settings();
			void quit();

			QList<QObject *> m_entries;
	};
}

#endif // MAINMENUSTATE_H
