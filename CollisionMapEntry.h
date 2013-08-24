#ifndef COLLISIONMAPENTRY_H
#define COLLISIONMAPENTRY_H

#include <QPolygon>
#include <QSet>

#include "OuterBounds.h"

using Coordinate = QPair<unsigned int, unsigned int>;

class CollisionMapEntry
{
	public:
		CollisionMapEntry();

		void addPoint(const int x, const int y);

		QList<QPoint> compile();

	private:
		QSet<Coordinate> m_coordinates;

		OuterBounds m_topLeft;
		OuterBounds m_bottomRight;
};

#endif // COLLISIONMAPENTRY_H
