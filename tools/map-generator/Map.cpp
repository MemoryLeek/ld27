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
			QPolygon polygon;
			QList<Coordinate> list = entry->compile();
			QSet<Coordinate> source = QSet<Coordinate>::fromList(list);
			QSet<Coordinate> target;

			const Coordinate *point = &list[0];

			while(point)
			{
				QMap<int, const Coordinate *> candidates;

				for(int x = -1; x <= 1; x++)
				{
					for(int y = -1; y <= 1; y++)
					{
						int tx = point->first + x;
						int ty = point->second + y;
						int score = abs(x) * abs(y);

						const Coordinate query(tx, ty);
						const Coordinate &result = *source.find(query);

						if(result != *source.end())
						{
							if(!target.contains(result))
							{
								candidates[score] = &result;
							}
						}
					}
				}

				if(!candidates.isEmpty())
				{
					const QList<const Coordinate *> coordinates = candidates.values();
					const Coordinate *c = coordinates.first();

					point = c;

					target << *point;
					polygon << QPoint(point->first, point->second);
				}
				else
				{
					point = 0;
				}
			}

			m_collidables << polygon;

			break;
		}

		case CollisionMapEntry::Path:
		{
			QPolygon polygon;
			QListEx<Coordinate> points = entry->compile();
			points.sort(&Utilities::compareCoordinate);

			for(int i = 0; i < points.count(); i += 20)
			{
				const Coordinate &coordinate = points[i];
				const QPoint point(coordinate.first, coordinate.second);
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
