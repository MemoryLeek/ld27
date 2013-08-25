#ifndef UTILITIES_H
#define UTILITIES_H

#include <QPoint>
#include <QPair>

using Coordinate = QPair<unsigned int, unsigned int>;

class Utilities
{
	public:
		static bool comparePoint(const QPoint &p1, const QPoint &p2)
		{
			return p1.x() > p2.x();
		}
};

#endif // UTILITIES_H
