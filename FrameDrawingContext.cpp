#include <QScopedPointer>

#include "FrameDrawingContext.h"

FrameDrawingContext::FrameDrawingContext(const QSize &size)
	: m_size(size)
{

}

QSize FrameDrawingContext::size() const
{
	return m_size;
}

Surface &FrameDrawingContext::background()
{
	return m_background;
}

Surface &FrameDrawingContext::foreground()
{
	return m_foreground;
}
