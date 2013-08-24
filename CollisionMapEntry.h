#ifndef COLLISIONMAPENTRY_H
#define COLLISIONMAPENTRY_H

#include <QPolygon>
#include <QSet>

#include "OuterBounds.h"

const int OFFSET = 10;

using Coordinate = QPair<unsigned int, unsigned int>;

class CollisionMapEntry
{
	public:
		CollisionMapEntry();

		void addPoint(const int x, const int y);

		QPolygon compile();

	private:
		QPoint findPoint(const QRect &rect);

		QSet<Coordinate> m_coordinates;

		OuterBounds m_topLeft;
		OuterBounds m_bottomRight;
};

#endif // COLLISIONMAPENTRY_H
