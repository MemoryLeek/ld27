#include <QPainter>

#include "Map.h"
#include "CollisionMapEntry.h"

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
	m_collidables << entry->compile();
}

QDataStream &operator <<(QDataStream &stream, const Map &map)
{
	stream << map.m_background;
	stream << map.m_foreground;
	stream << map.m_collidables;

	return stream;
}
