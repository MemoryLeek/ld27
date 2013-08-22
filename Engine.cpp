#include <QtQml>

#include "Engine.h"
#include "Window.h"

Engine::Engine()
{
	qmlRegisterType<Window>("MemoryLeek", 1, 0, "Window");
}
