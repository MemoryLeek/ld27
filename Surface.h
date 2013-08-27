#ifndef SURFACE_H
#define SURFACE_H

#include <QImage>
#include <QPaintDevice>

#include "ICollectionItem.h"
#include "DeferredPaintEngine.h"

class Surface : public QPaintDevice
{
	public:
		Surface(const QSize &size);

		QPaintEngine *paintEngine() const override;

		void draw(QPainter *painter) const;

	private:
		int metric(PaintDeviceMetric metric) const override;

		DeferredPaintEngine m_engine;
		QSize m_size;
};

#endif // SURFACE_H
