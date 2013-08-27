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
	context.addSurface(&m_image, -cx, -cy, m_surfaceLevel);
}
