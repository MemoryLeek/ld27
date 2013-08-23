#include <QGuiApplication>

#include "MenuState.h"
#include "MenuEntry.h"

#include "States/DummyState.h"

namespace States
{
	MenuState::MenuState()
	{
		m_selectedIndex = 0;
		m_entries =
		{
			new MenuEntry<MenuState>("Start", this, &MenuState::start),
			new MenuEntry<MenuState>("Dummy entry (Segfault)", this, 0),
			new MenuEntry<MenuState>("Quit", this, &MenuState::quit)
		};
	}

	QList<QObject *> MenuState::entries()
	{
		return m_entries;
	}

	int MenuState::selectedIndex() const
	{
		return m_selectedIndex;
	}

	void MenuState::keyPressEvent(QKeyEvent *event)
	{
		if(!event->isAutoRepeat())
		{
			const int count = m_entries.count();
			const int max = count - 1;

			switch(event->key())
			{
				case Qt::Key_Up:
				{
					if(m_selectedIndex > 0)
					{
						m_selectedIndex--;
					}
					else
					{
						m_selectedIndex = max;
					}

					break;
				}

				case Qt::Key_Down:
				{
					if(m_selectedIndex < max)
					{
						m_selectedIndex++;
					}
					else
					{
						m_selectedIndex = 0;
					}

					break;
				}

				case Qt::Key_Return:
				{
					QObject *object = m_entries[m_selectedIndex];
					IMenuEntry *entry = (IMenuEntry *)object;
					entry->invoke();

					break;
				}
			}

			emit selectedIndexChanged();
		}
	}

	void MenuState::start()
	{
		changeState<States::DummyState>();
	}

	void MenuState::quit()
	{
		qApp->quit();
	}
}
