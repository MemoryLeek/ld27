#include "SettingsMenuState.h"
#include "MenuEntry.h"

namespace States
{
	SettingsMenuState::SettingsMenuState()
	{
		m_entries =
		{
			new MenuEntry<SettingsMenuState>("Display settings", 0, 0)
		};
	}

	QList<QObject *> SettingsMenuState::entries()
	{
		return m_entries;
	}
}
