#include <QGuiApplication>

#include "MainMenuState.h"
#include "MenuEntry.h"

#include "States/DummyState.h"
#include "States/SettingsMenuState.h"

namespace States
{
	MainMenuState::MainMenuState()
	{
		m_entries =
		{
			new MenuEntry<MainMenuState>("Start", this, &MainMenuState::start),
			new MenuEntry<MainMenuState>("Settings", this, &MainMenuState::settings),
			new MenuEntry<MainMenuState>("Quit", this, &MainMenuState::quit)
		};
	}

	QList<QObject *> MainMenuState::entries()
	{
		return m_entries;
	}

	void MainMenuState::start()
	{
		changeState<States::DummyState>();
	}

	void MainMenuState::settings()
	{
		changeState<States::SettingsMenuState>();
	}

	void MainMenuState::quit()
	{
		qApp->quit();
	}
}
