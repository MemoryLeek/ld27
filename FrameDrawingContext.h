#ifndef FRAMEDRAWINGCONTEXT_H
#define FRAMEDRAWINGCONTEXT_H

#include <QPainter>
#include <QImage>

#include "Surface.h"
#include "QListEx.h"

class FrameDrawingContext
{
	public:
		FrameDrawingContext(const QSize &size);

		QImage &background();
		QImage &foreground();

	private:
		QImage m_background;
		QImage m_foreground;
};

#endif // FRAMEDRAWINGCONTEXT_H
