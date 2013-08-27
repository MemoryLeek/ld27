#ifndef COMPOSITOR_H
#define COMPOSITOR_H

#include <QPainter>

class FrameDrawingContext;

class Compositor
{
	public:
		Compositor();

		void composite(FrameDrawingContext &context, QPainter *painter);
};

#endif // COMPOSITOR_H
