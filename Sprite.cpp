#include "Sprite.h"
#include "Scene.h"

Sprite::Sprite()
{
	m_index = 0;
	m_delay = 0;
}

void Sprite::update(const int delta)
{
	const float f = (delta / 1000.0f) * (1000.0f / m_delay);
	const float c = m_index + f;
	const float i1 = c < m_frames.count() ? c : 0;
	const float i2 = i1 > -1 ? i1 : m_frames.count() - 1;

	m_index = i2;
}

QImage Sprite::currentFrame(const bool flipped) const
{
	const QImage &frame = m_frames[m_index];
	const QImage &adjusted = frame.mirrored(flipped, false);

	return adjusted;
}

float Sprite::delay() const
{
	return m_delay;
}

int Sprite::frameCount() const
{
	return m_frames.count();
}

QDataStream &operator >>(QDataStream &stream, Sprite &sprite)
{
	stream >> sprite.m_delay;
	stream >> sprite.m_frames;

	return stream;
}
