#ifndef SURFACE_H
#define SURFACE_H

#include <QImage>
#include <QPaintDevice>
#include <QAtomicInt>

#include "ICollectionItem.h"
#include "DeferredPaintEngine.h"

class Surface : public QPaintDevice
{
	public:
		QPaintEngine *paintEngine() const override;

		void draw(QPainter *painter) const;

	private:
		int metric(PaintDeviceMetric) const override;

		DeferredPaintEngine m_engine;
};

#endif // SURFACE_H
