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

			virtual QList<QObject *> entries() = 0;

			int selectedIndex() const;

		private:
			void initialize() override;
			void complete() override;
			void keyPressEvent(QKeyEvent *event) override;

			int m_selectedIndex;

		signals:
			void entriesChanged();
			void selectedIndexChanged();
	};
}

#endif // MENUSTATE_H
