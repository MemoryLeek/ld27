#include <QtQml>

#include "Engine.h"
#include "Window.h"
#include "LocalImageProvider.h"
#include "FrameImageProvider.h"
#include "SharedState.h"
#include "Compositor.h"
#include "StateHandler.h"

#include "States/LogoState.h"
#include "States/MainMenuState.h"
#include "States/GameState.h"
#include "States/GoalState.h"
#include "States/DeathState.h"

Engine::Engine()
{
	m_compositor = new Compositor();
	m_sharedState = new SharedState();
	m_stateHandler = new StateHandler(this);
	m_localImageProvider = new LocalImageProvider();
	m_frameImageProvider = new FrameImageProvider(m_compositor);

	// Registration of QML types
	qmlRegisterType<Window>("MemoryLeek", 1, 0, "Window");
	qmlRegisterType<States::LogoState>("MemoryLeek", 1, 0, "LogoState");
	qmlRegisterType<States::MainMenuState>("MemoryLeek", 1, 0, "MenuState");
	qmlRegisterType<States::GameState>("MemoryLeek", 1, 0, "GameState");
	qmlRegisterType<States::GoalState>("MemoryLeek", 1, 0, "GoalState");
	qmlRegisterType<States::DeathState>("MemoryLeek", 1, 0, "DeathState");

	// Registration of components
	registerComponent(m_sharedState);
	registerComponent(m_compositor);
	registerComponent(m_stateHandler);

	// Registration of image providers
	addImageProvider("local", m_localImageProvider);
	addImageProvider("frame", m_frameImageProvider);
}
