#include "Compositor.h"
#include "FrameDrawingContext.h"

QImage Compositor::lastFrame() const
{
	const QSize size = m_lastFrame->size();
	const Surface &background = m_lastFrame->background();
	const Surface &foreground = m_lastFrame->foreground();

	QImage image(size, QImage::Format_RGB888);
	QPainter painter(&image);

	background.draw(&painter);
	foreground.draw(&painter);

	return image;
}

void Compositor::composite(FrameDrawingContext *context, QPainter *painter)
{
	const Surface &background = context->background();
	const Surface &foreground = context->foreground();

	background.draw(painter);
	foreground.draw(painter);

	m_lastFrame.reset(context);
}
