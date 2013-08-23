#include <QtQml>

#include "Engine.h"
#include "Window.h"

#include "States/LogoState.h"
#include "States/MenuState.h"
#include "States/DummyState.h"

Engine::Engine()
{
	qmlRegisterType<Window>("MemoryLeek", 1, 0, "Window");
	qmlRegisterType<States::LogoState>("MemoryLeek", 1, 0, "LogoState");
	qmlRegisterType<States::MenuState>("MemoryLeek", 1, 0, "MenuState");
	qmlRegisterType<States::DummyState>("MemoryLeek", 1, 0, "DummyState");
}
