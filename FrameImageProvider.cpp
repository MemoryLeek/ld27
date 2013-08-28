#include "FrameImageProvider.h"
#include "Compositor.h"

FrameImageProvider::FrameImageProvider(Compositor *compositor)
	: QQuickImageProvider(QQuickImageProvider::Image)
{
	m_compositor = compositor;
}

QImage FrameImageProvider::requestImage(const QString &, QSize *, const QSize &)
{
	return m_compositor->lastFrame();
}
