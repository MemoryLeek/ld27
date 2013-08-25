#include "MenuState.h"
#include "MenuEntry.h"

namespace States
{
	MenuState::MenuState()
	{
		m_selectedIndex = 0;
	}

	int MenuState::selectedIndex() const
	{
		return m_selectedIndex;
	}

	void MenuState::initialize()
	{
		/* No implementation */
	}

	void MenuState::complete()
	{
		/* No implementation */
	}

	void MenuState::keyPressEvent(QKeyEvent *event)
	{
		if(!event->isAutoRepeat())
		{
			QList<QObject *> list = entries();

			const int count = list.count();
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
					QList<QObject *> list = entries();
					QObject *object = list[m_selectedIndex];

					IMenuEntry *entry = (IMenuEntry *)object;
					entry->invoke();

					break;
				}
			}

			emit selectedIndexChanged();
		}
	}
}
