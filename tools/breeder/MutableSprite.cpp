#include "MutableSprite.h"

void MutableSprite::addFrame(const QImage image)
{
	m_frames << image;
}

void MutableSprite::setDelay(const float delay)
{
	m_delay = delay;
}

bool MutableSprite::isValid() const
{
	return !m_frames.isEmpty();
}
