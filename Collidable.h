#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <QDataStream>
#include <QPolygon>
#include <QRect>

class Collidable
{
	public:
		Collidable();

		QPolygon polygon() const;
		QRect boundingBox() const;

	private:
		friend QDataStream &operator >>(QDataStream &stream, Collidable &collidable);

		QPolygon m_polygon;
		QRect m_boundingBox;
};

#endif // COLLIDABLE_H
