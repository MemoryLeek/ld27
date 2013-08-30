#include <QGuiApplication>

#include "DeathState.h"
#include "MenuEntry.h"
#include "StateHandler.h"

#include "States/GameState.h"

namespace States
{
	DeathState::DeathState()
	{
		m_entries =
		{
			new MenuEntry<DeathState>("Retry", this, &DeathState::retry),
			new MenuEntry<DeathState>("Quit", this, &DeathState::quit)
		};
	}

	QList<QObject *> DeathState::entries()
	{
		return m_entries;
	}

	void DeathState::retry()
	{
		m_stateHandler->changeState<States::GameState>();
	}

	void DeathState::quit()
	{
		qApp->quit();
	}

	void DeathState::initialize()
	{
		m_stateHandler = getComponent<StateHandler>();
	}

	void DeathState::complete()
	{

	}
}
