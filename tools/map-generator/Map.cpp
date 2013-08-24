#include <QPainter>

#include "Map.h"
#include "CollisionMapEntry.h"
#include "QListEx.h"

void Map::setBackground(const QImage &background)
{
	m_background = background;
}

void Map::setForeground(const QImage &foreground)
{
	m_foreground = foreground;
}

void Map::addCollisionMapEntry(CollisionMapEntry *entry)
{
	switch(entry->type())
	{
		case CollisionMapEntry::Collision:
		{
			m_collidables << entry->compile();

			break;
		}

		case CollisionMapEntry::Path:
		{
			QPolygon polygon;
			QListEx<QPoint> points = entry->compile();
			points.sort(&Utilities::comparePoint);

			for(int i = 0; i < points.count(); i += 20)
			{
				const QPoint &point = points[i];
				const QPoint adjusted = point - QPoint(0, 60);

				polygon << adjusted;
			}

			m_paths << polygon;

			break;
		}
	}
}

QDataStream &operator <<(QDataStream &stream, const Map &map)
{
	stream << map.m_background;
	stream << map.m_foreground;
	stream << map.m_collidables;
	stream << map.m_paths;

	return stream;
}
