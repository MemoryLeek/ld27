#include "Collidable.h"

Collidable::Collidable()
{

}

QPolygon Collidable::polygon() const
{
	return m_polygon;
}

QRect Collidable::boundingBox() const
{
	return m_boundingBox;
}

QDataStream &operator >>(QDataStream &stream, Collidable &collidable)
{
	stream >> collidable.m_polygon;
	stream >> collidable.m_boundingBox;

	return stream;
}
