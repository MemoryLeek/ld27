#include <QtQml>

#include "Engine.h"
#include "Window.h"
#include "LocalImageProvider.h"

#include "States/LogoState.h"
#include "States/MainMenuState.h"
#include "States/DummyState.h"

Engine::Engine()
{
	m_localImageProvider = new LocalImageProvider();

	// Registration of QML types
	qmlRegisterType<Window>("MemoryLeek", 1, 0, "Window");
	qmlRegisterType<States::LogoState>("MemoryLeek", 1, 0, "LogoState");
	qmlRegisterType<States::MainMenuState>("MemoryLeek", 1, 0, "MenuState");
	qmlRegisterType<States::DummyState>("MemoryLeek", 1, 0, "DummyState");

	// Registration of image providers
	addImageProvider("local", m_localImageProvider);
}
