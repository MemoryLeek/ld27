#ifndef FRAMEDRAWINGCONTEXT_H
#define FRAMEDRAWINGCONTEXT_H

#include <QPainter>
#include <QImage>

#include "Surface.h"
#include "QListEx.h"

class FrameDrawingContext
{
	public:
		FrameDrawingContext(QPainter *painter);
		~FrameDrawingContext();

		QImage *createSurface(const int order);
		QImage *addSurface(QImage *image, const int x, const int y, const int order);

	private:
		QPainter *m_painter;
		QListEx<Surface> m_surfaces;
};

#endif // FRAMEDRAWINGCONTEXT_H
