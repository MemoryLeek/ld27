#include <QDebug>

#include "Surface.h"

QPaintEngine *Surface::paintEngine() const
{
	Surface *surface = const_cast<Surface *>(this);
	DeferredPaintEngine &engine = surface->m_engine;

	return &engine;
}

void Surface::draw(QPainter *painter) const
{
	m_engine.draw(painter);
}

int Surface::metric(QPaintDevice::PaintDeviceMetric) const
{
	return 0;
}
