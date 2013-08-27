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

		Surface &background();
		Surface &foreground();

	private:
		Surface m_background;
		Surface m_foreground;
};

#endif // FRAMEDRAWINGCONTEXT_H
