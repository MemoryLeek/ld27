#include "Compositor.h"
#include "FrameDrawingContext.h"

Compositor::Compositor()
{

}

void Compositor::composite(FrameDrawingContext &context, QPainter *painter)
{
	const QImage &background = context.background();
	const QImage &foreground = context.foreground();
	const QPoint position;

	painter->drawImage(position, background);
	painter->drawImage(position, foreground);
}
