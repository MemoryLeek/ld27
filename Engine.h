#ifndef ENGINE_H
#define ENGINE_H

#include <QQmlEngine>

#include "Container.h"

class LocalImageProvider;

class Engine
	: public QQmlEngine
	, public Container
{
	public:
		Engine();

	private:
		LocalImageProvider *m_localImageProvider;
};

#endif // ENGINE_H
