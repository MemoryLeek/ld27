#include <QDebug>

#include "CollisionMapEntry.h"
#include "LookupResult.h"

CollisionMapEntry::CollisionMapEntry()
{

}

void CollisionMapEntry::addPoint(const int x, const int y)
{
	m_topLeft.tryExtend(OuterBounds::TopLeft, x, y);
	m_bottomRight.tryExtend(OuterBounds::BottomRight, x, y);
	m_coordinates << Coordinate(x, y);
}

QList<QPoint> CollisionMapEntry::compile()
{
	QList<QPoint> points;

	foreach(const Coordinate &coordinate, m_coordinates)
	{
		int offset = 1;
		int size = offset * 2;
		int x = coordinate.first;
		int y = coordinate.second;
		int hits = 0;

		for(int xr = x - offset; xr < x + size; xr++)
		{
			for(int yr = y - offset; yr < y + size; yr++)
			{
				Coordinate query(xr, yr);
				LookupResult result = m_coordinates.contains(query);

				if(result.isValid())
				{
					hits++;
				}
			}
		}

		if(hits < 8)
		{
			points << QPoint(x, y);
		}
	}

	return points;
}
