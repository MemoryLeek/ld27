#include <QScopedPointer>

#include "FrameDrawingContext.h"
#include "Frame.h"

FrameDrawingContext::FrameDrawingContext()
{

}

FrameDrawingContext::FrameDrawingContext(const QSize &size)
	: m_frame(new Frame)
	, m_size(size)
{

}

QSize FrameDrawingContext::size() const
{
	return m_size;
}

Surface &FrameDrawingContext::background()
{
	return m_frame->background();
}

Surface &FrameDrawingContext::foreground()
{
	return m_frame->foreground();
}
