#include <QDebug>

#include "Surface.h"

Surface::Surface(QSize size, const int order)
{
	m_image = new QImage(size, QImage::Format_ARGB32);
	m_order = order;
	m_managed = true;
}

Surface::Surface(QImage *image, QPoint position, const int order)
{
	m_image = image;
	m_position = position;
	m_order = order;
	m_managed = false;
}

QImage *Surface::image()
{
	return m_image;
}

QPoint Surface::position() const
{
	return m_position;
}

bool Surface::isManaged() const
{
	return m_managed;
}

bool Surface::compare(const Surface &s1, const Surface &s2)
{
	return s1.m_order < s2.m_order;
}
