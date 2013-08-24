#include <QPainter>

#include "Map.h"
#include "Scene.h"
#include "MapSurface.h"

void Map::initialize(Scene *scene)
{
	m_backgroundSurface = new MapSurface(MapSurface::Background, m_background, scene);
	m_foregroundSurface = new MapSurface(MapSurface::Foreground, m_foreground, scene);

	QSize size = m_background.size();
	QImage foo(size, QImage::Format_ARGB32);
	QPainter painter(&foo);

	for(const QPoint &point : m_collidables)
	{
		painter.setPen(Qt::red);
		painter.setBrush(Qt::red);
		painter.drawPoint(point);
	}

	new MapSurface(MapSurface::Foreground, foo, scene);
}

int Map::width() const
{
	return m_background.width();
}

int Map::height() const
{
	return m_background.height();
}

bool Map::isCollidable(const int x, const int y)
{
	QPoint p(x, y);

	return m_collidables.contains(p);
}

QDataStream &operator >>(QDataStream &stream, Map &map)
{
	stream >> map.m_background;
	stream >> map.m_foreground;
	stream >> map.m_collidables;

	return stream;
}
