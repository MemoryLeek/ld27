#include <QtQml>

#include "Engine.h"
#include "Window.h"

#include "States/LogoState.h"

Engine::Engine()
{
	qmlRegisterType<Window>("MemoryLeek", 1, 0, "Window");
	qmlRegisterType<States::LogoState>("MemoryLeek", 1, 0, "LogoState");
}
