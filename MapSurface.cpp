#include <QPainter>

#include "MapSurface.h"
#include "FrameDrawingContext.h"
#include "Scene.h"
#include "Surface.h"

MapSurface::MapSurface(const SurfaceLevel surfaceLevel, const QImage &image)
{
	m_surfaceLevel = surfaceLevel;
	m_image = image;
}

void MapSurface::draw(FrameDrawingContext &context, const int cx, const int cy, const int delta)
{
	switch(m_surfaceLevel)
	{
		case Background:
		{
			Surface &surface = context.background();
			QPainter painter(&surface);
			painter.drawImage(-cx, -cy, m_image);

			break;
		}

		case Foreground:
		{
			Surface &surface = context.foreground();
			QPainter painter(&surface);
			painter.drawImage(-cx, -cy, m_image);

			break;
		}
	}
}
