#ifndef UTILITIES_H
#define UTILITIES_H

#include <QPoint>
#include <QPair>
#include <QLine>

using Coordinate = QPair<unsigned int, unsigned int>;

class Utilities
{
	public:
		static bool compareCoordinate(const Coordinate &p1, const Coordinate &p2)
		{
			return p1.first > p2.first;
		}
};

#endif // UTILITIES_H
