#include <QDebug>

#include "Surface.h"

Surface::Surface(const QSize &size)
	: m_size(size)
{

}

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

int Surface::metric(QPaintDevice::PaintDeviceMetric metric) const
{
	switch(metric)
	{
		case QPaintDevice::PdmWidth:
		{
			return m_size.width();
		}

		case QPaintDevice::PdmHeight:
		{
			return m_size.height();
		}

		case QPaintDevice::PdmDepth:
		{
			return 32;
		}

		default:
		{
			return 0;
		}
	}
}
