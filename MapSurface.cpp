#include "MapSurface.h"
#include "Scene.h"

MapSurface::MapSurface(const SurfaceLevel surfaceLevel, const QImage &image, Scene *scene)
	: IDrawable(scene)
{
	m_surfaceLevel = surfaceLevel;
	m_texture = scene->createTexture(image);

	qDebug() << "MapSurface";
}

MapSurface::~MapSurface()
{
	delete m_texture;
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

QSGTexture *MapSurface::texture()
{
	return m_texture;
}
