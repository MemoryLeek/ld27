#include <QtQml>

#include "Engine.h"
#include "Window.h"
#include "LocalImageProvider.h"
#include "SharedState.h"

#include "States/LogoState.h"
#include "States/MainMenuState.h"
#include "States/GameState.h"
#include "States/GoalState.h"

Engine::Engine()
{
	m_localImageProvider = new LocalImageProvider();
	m_sharedState = new SharedState();

	// Registration of QML types
	qmlRegisterType<Window>("MemoryLeek", 1, 0, "Window");
	qmlRegisterType<States::LogoState>("MemoryLeek", 1, 0, "LogoState");
	qmlRegisterType<States::MainMenuState>("MemoryLeek", 1, 0, "MenuState");
	qmlRegisterType<States::GameState>("MemoryLeek", 1, 0, "GameState");
	qmlRegisterType<States::GoalState>("MemoryLeek", 1, 0, "GoalState");

	// Registration of components
	registerComponent(m_sharedState);

	// Registration of image providers
	addImageProvider("local", m_localImageProvider);
}
