#ifndef ENGINE_H
#define ENGINE_H

#include <QQmlEngine>

#include "Container.h"

class SharedState;
class LocalImageProvider;
class FrameImageProvider;
class Compositor;

class Engine
	: public QQmlEngine
	, public Container
{
	public:
		Engine();

	private:
		Compositor *m_compositor;
		SharedState *m_sharedState;
		LocalImageProvider *m_localImageProvider;
		FrameImageProvider *m_frameImageProvider;
};

#endif // ENGINE_H
