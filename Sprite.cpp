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
	const float index = c < m_frames.count() ? c : 0;

	m_index = index;
}

QImage Sprite::currentFrame(const bool flipped)
{
	const int i = m_index;
	const int count = m_frames.count();
	const int index = i <= count ? i : 0;
	const int foo = index < 0 ? count - 1 : index;
	const int identifier = foo + count * flipped;

	const QImage &m = m_textures.value(identifier);

	if(m.isNull())
	{
		return createTexture(foo, flipped);
	}

	return m;
}

float Sprite::delay() const
{
	return m_delay;
}

int Sprite::frameCount() const
{
	return m_frames.count();
}

QImage Sprite::createTexture(const int index, const bool flipped)
{
	QImage image = m_frames[index];
	QImage adjusted = image.mirrored(flipped, false);

	const int count = m_frames.count();
	const int identifier = index + count * flipped;

	qDebug() << "Creating new texture with id" << identifier;

	return m_textures
		.insert(identifier, adjusted)
		.value();
}

QDataStream &operator >>(QDataStream &stream, Sprite &sprite)
{
	stream >> sprite.m_delay;
	stream >> sprite.m_frames;

	return stream;
}
