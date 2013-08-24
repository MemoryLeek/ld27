#ifndef COLLISIONMAPENTRY_H
#define COLLISIONMAPENTRY_H

#include <QPolygon>
#include <QPair>
#include <QSet>

#include "Utilities.h"

class CollisionMapEntry
{
	public:
		enum EntryType
		{
			Collision = 4294901760,
			Path = 4278255360
		};

		CollisionMapEntry(EntryType type);

		void addPoint(const int x, const int y);

		EntryType type() const;
		QList<QPoint> compile() const;

	private:
		EntryType m_type;
		QSet<Coordinate> m_coordinates;
};

#endif // COLLISIONMAPENTRY_H
