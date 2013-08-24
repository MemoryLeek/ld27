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

QPolygon CollisionMapEntry::compile()
{
	QPolygon polygon;

	const int x1 = m_topLeft.x();
	const int y1 = m_topLeft.y();
	const int x2 = m_bottomRight.x() - x1;
	const int y2 = m_bottomRight.y() - y1;

	for(int xr = x1; xr < x2; xr += OFFSET)
	{
		for(int yr = y1; yr < y2; yr += OFFSET)
		{
			QRect rect(xr, yr, OFFSET, OFFSET);
			QPoint nearest = findPoint(rect);

			if(!nearest.isNull())
			{
				polygon << nearest;
			}
		}
	}

	return polygon;
}

QPoint CollisionMapEntry::findPoint(const QRect &rect)
{
	const int x = rect.x() + rect.width() / 2;
	const int y = rect.y() + rect.height() / 2;

	for(int radius = 0; radius < OFFSET; radius++)
	{
		const int size = radius * 2;

		for(int xr = x - radius; xr < x + size; xr++)
		{
			for(int yr = y - radius; yr < y + size; yr++)
			{
				Coordinate query(xr, yr);
				LookupResult result = m_coordinates.contains(query);

				if(result.isValid())
				{
					return QPoint(xr, yr);
				}
			}
		}
	}

	return QPoint();
}
