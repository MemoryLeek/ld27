#ifndef FRAMEDRAWINGCONTEXT_H
#define FRAMEDRAWINGCONTEXT_H

#include <QSize>
#include <QSharedPointer>

class Surface;
class Frame;

class FrameDrawingContext
{
	public:
		FrameDrawingContext();
		FrameDrawingContext(const QSize &size);

		QSize size() const;

		Surface &background();
		Surface &foreground();

	private:
		QSharedPointer<Frame> m_frame;
		QSize m_size;
};

#endif // FRAMEDRAWINGCONTEXT_H
