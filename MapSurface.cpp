#include <QPainter>

#include "MapSurface.h"
#include "Scene.h"

MapSurface::MapSurface(const SurfaceLevel surfaceLevel, const QImage &image, Scene *scene)
	: IDrawable(scene)
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

void MapSurface::draw(QPainter *painter, const int cx, const int cy, const int delta)
{
	painter->drawImage(-cx, -cy, m_image);
}
