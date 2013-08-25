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

	for(const QPolygon &polygon : m_collidables)
	{
		painter.setPen(Qt::red);
		painter.setBrush(Qt::NoBrush);
		painter.drawPolygon(polygon);
	}

	QLine spawnLine(m_spawn.x(), 0, m_spawn.x(), size.height());

	painter.setBrush(Qt::blue);
	painter.setPen(Qt::blue);
	painter.drawLine(spawnLine);
	painter.drawEllipse(m_spawn, 10, 10);

	painter.fillRect(m_goal, Qt::yellow);

//	for(const QPolygon &path : m_paths)
//	{
//		qDebug() << path.count();

//		const QPoint *previous = 0;

//		for(const QPoint &point : path)
//		{
//			if(previous)
//			{
//				QLine line(*previous, point);

//				painter.setBrush(Qt::NoBrush);
//				painter.setPen(Qt::green);
//				painter.drawLine(line);

//				painter.setBrush(Qt::blue);
//				painter.setPen(Qt::blue);
//				painter.drawEllipse(*previous, 10, 10);

//				previous = &point;
//			}
//			else
//			{
//				previous = &point;
//			}
//		}
//	}

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

QList<QPolygon> Map::collidables() const
{
	return m_collidables;
}

QList<QPolygon> Map::paths() const
{
	return m_paths;
}

QDataStream &operator >>(QDataStream &stream, Map &map)
{
	stream >> map.m_background;
	stream >> map.m_foreground;
	stream >> map.m_collidables;
	stream >> map.m_paths;
	stream >> map.m_spawn;
	stream >> map.m_goal;

	return stream;
}
