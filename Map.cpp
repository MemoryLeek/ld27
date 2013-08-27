#include <QPainter>

#include "Map.h"
#include "Scene.h"
#include "MapSurface.h"
#include "FrameDrawingContext.h"

void Map::initialize(Scene *scene)
{
	m_backgroundSurface = new MapSurface(MapSurface::Background, m_background, scene);
	m_foregroundSurface = new MapSurface(MapSurface::Foreground, m_foreground, scene);

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

//	new MapSurface(MapSurface::Foreground, foo, scene);
}

int Map::width() const
{
	return m_background.width();
}

int Map::height() const
{
	return m_background.height();
}

void Map::draw(FrameDrawingContext &context, const int cx, const int cy, const int delta)
{
	m_backgroundSurface->draw(context, cx, cy, delta);
	m_foregroundSurface->draw(context, cx, cy, delta);

#ifndef QT_NO_DEBUG
	QPoint cameraPosition(cx, cy);
	QImage *surface = context.createSurface(2);

	QPainter painter(surface);
	painter.translate(-cameraPosition);

	for(const Collidable &collidable : m_collidables)
	{
		const QPolygonF &polygon = collidable.polygon();
		const QRect &boundingBox = collidable.boundingBox();

		painter.setPen(Qt::red);
		painter.setBrush(Qt::NoBrush);
		painter.drawPolygon(polygon);

		painter.setPen(Qt::green);
		painter.setBrush(Qt::NoBrush);
		painter.drawRect(boundingBox);
	}
#endif
}

QList<Collidable> Map::collidables() const
{
	return m_collidables;
}

QList<QPolygon> Map::paths() const
{
	return m_paths;
}

QPoint Map::spawnPoint() const
{
	return m_spawn;
}

QRect Map::goal() const
{
	return m_goal;
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
