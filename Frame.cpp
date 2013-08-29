#include <QDebug>

#include "Frame.h"

Surface &Frame::background()
{
	return m_background;
}

Surface &Frame::foreground()
{
	return m_foreground;
}
