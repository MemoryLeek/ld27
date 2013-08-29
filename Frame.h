#ifndef FRAME_H
#define FRAME_H

#include <QSize>
#include <QSharedData>

#include "Surface.h"

class Frame
{
	public:
		Surface &background();
		Surface &foreground();

	private:
		Surface m_background;
		Surface m_foreground;
};

#endif // FRAME_H
