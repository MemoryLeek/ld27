#include "Compositor.h"
#include "FrameDrawingContext.h"

Compositor::Compositor()
{

}

void Compositor::composite(FrameDrawingContext &context, QPainter *painter)
{
	const Surface &background = context.background();
	const Surface &foreground = context.foreground();

	background.draw(painter);
	foreground.draw(painter);
}
