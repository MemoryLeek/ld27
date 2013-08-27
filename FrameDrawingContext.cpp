#include <QScopedPointer>

#include "FrameDrawingContext.h"

FrameDrawingContext::FrameDrawingContext(const QSize &size)
	: m_background(size)
	, m_foreground(size)
{

}

Surface &FrameDrawingContext::background()
{
	return m_background;
}

Surface &FrameDrawingContext::foreground()
{
	return m_foreground;
}
