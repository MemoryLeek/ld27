#include <QPainter>

#include "MapSurface.h"
#include "FrameDrawingContext.h"
#include "Scene.h"

MapSurface::MapSurface(const SurfaceLevel surfaceLevel, const QImage &image, Scene *scene)
{
	m_surfaceLevel = surfaceLevel;
	m_image = image;
}

float MapSurface::x() const
{
	return 0;
}

float MapSurface::y() const
{
	return 0;
}

unsigned int MapSurface::drawingOrder() const
{
	return m_surfaceLevel;
}

void MapSurface::draw(FrameDrawingContext &context, const int cx, const int cy, const int delta)
{
	switch(m_surfaceLevel)
	{
		case Background:
		{
			QImage &m = context.background();
			QPainter painter(&m);
			painter.drawImage(-cx, -cy, m_image);

			break;
		}

		case Foreground:
		{
			QImage &m = context.foreground();
			QPainter painter(&m);
			painter.drawImage(-cx, -cy, m_image);

			break;
		}
	}
}
