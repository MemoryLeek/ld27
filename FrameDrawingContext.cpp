#include <QScopedPointer>

#include "FrameDrawingContext.h"

FrameDrawingContext::FrameDrawingContext(QPainter *painter)
{
	m_painter = painter;
}

FrameDrawingContext::~FrameDrawingContext()
{
	m_surfaces.sort(&Surface::compare);

	for(Surface surface : m_surfaces)
	{
		const QImage *image = surface.image();
		const QPoint &position = surface.position();

		m_painter->drawImage(position, *image);

		if(surface.isManaged())
		{
			delete image;
		}
	}
}

QImage *FrameDrawingContext::createSurface(const int order)
{
	QRect window = m_painter->window();
	QSize size = window.size();

	Surface surface(size, order);
	surface.addTo(m_surfaces);

	return surface.image();
}

QImage *FrameDrawingContext::addSurface(QImage *image, const int x, const int y, const int order)
{
	QPoint position(x, y);

	Surface surface(image, position, order);
	surface.addTo(m_surfaces);

	return surface.image();
}
