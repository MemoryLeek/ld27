#include "Map.h"

Map::Map()
{

}

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
	m_entries << entry;
}
