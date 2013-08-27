#include <QScopedPointer>

#include "FrameDrawingContext.h"

FrameDrawingContext::FrameDrawingContext(const QSize &size)
	: m_background(size, QImage::Format_ARGB32)
	, m_foreground(size, QImage::Format_ARGB32)
{

}

QImage &FrameDrawingContext::background()
{
	return m_background;
}

QImage &FrameDrawingContext::foreground()
{
	return m_foreground;
}
