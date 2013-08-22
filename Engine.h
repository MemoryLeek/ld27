#ifndef ENGINE_H
#define ENGINE_H

#include <QQmlEngine>

#include "Container.h"

class Engine
	: public QQmlEngine
	, public Container
{
	public:
		Engine();
};

#endif // ENGINE_H
