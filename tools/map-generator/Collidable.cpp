#include "Collidable.h"

Collidable::Collidable(const QPolygon &polygon)
{
	m_polygon = polygon;
}

QDataStream &operator <<(QDataStream &stream, const Collidable &collidable)
{
	const QPolygon &polygon = collidable.m_polygon;
	const QRect rect = polygon.boundingRect();

	stream << polygon;
	stream << rect;

	return stream;
}
