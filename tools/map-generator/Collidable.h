#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <QPolygon>
#include <QDataStream>

class Collidable
{
	public:
		Collidable(const QPolygon &polygon);

	private:
		friend QDataStream &operator <<(QDataStream &stream, const Collidable &collidable);

		QPolygon m_polygon;
};

#endif // COLLIDABLE_H
