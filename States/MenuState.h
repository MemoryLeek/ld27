#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"

namespace States
{
	class MenuState : public State
	{
		Q_OBJECT

		Q_PROPERTY(QList<QObject *> entries READ entries NOTIFY entriesChanged)
		Q_PROPERTY(int selectedIndex READ selectedIndex NOTIFY selectedIndexChanged)

		public:
			MenuState();

			QList<QObject *> entries();
			int selectedIndex() const;

		private:
			void keyPressEvent(QKeyEvent *event) override;

			void start();
			void quit();

			QList<QObject *> m_entries;
			int m_selectedIndex;

		signals:
			void entriesChanged();
			void selectedIndexChanged();
	};
}

#endif // MENUSTATE_H