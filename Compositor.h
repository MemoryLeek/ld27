#ifndef COMPOSITOR_H
#define COMPOSITOR_H

#include <QPainter>

#include "FrameDrawingContext.h"

class Compositor
{
	public:
		QImage lastFrame() const;

		void composite(FrameDrawingContext *context, QPainter *painter);

	private:
		QSharedPointer<FrameDrawingContext> m_lastFrame;
};

#endif // COMPOSITOR_H
