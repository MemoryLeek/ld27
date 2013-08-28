#ifndef FRAMEDRAWINGCONTEXT_H
#define FRAMEDRAWINGCONTEXT_H

#include <QPainter>
#include <QImage>

#include "Surface.h"
#include "QListEx.h"

class Compositor;

class FrameDrawingContext
{
	public:
		FrameDrawingContext(const QSize &size);

		QSize size() const;

		Surface &background();
		Surface &foreground();

	private:
		QSize m_size;

		Surface m_background;
		Surface m_foreground;
};

#endif // FRAMEDRAWINGCONTEXT_H
