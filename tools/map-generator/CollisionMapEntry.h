#ifndef COLLISIONMAPENTRY_H
#define COLLISIONMAPENTRY_H

#include <QPolygon>
#include <QPair>
#include <QSet>

using Coordinate = QPair<unsigned int, unsigned int>;

class CollisionMapEntry
{
	public:
		void addPoint(const int x, const int y);

		QList<QPoint> compile();

	private:
		QSet<Coordinate> m_coordinates;
};

#endif // COLLISIONMAPENTRY_H
