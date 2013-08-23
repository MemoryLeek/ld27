#include "AnimatedSprite.h"
#include "Scene.h"

AnimatedSprite::AnimatedSprite(const QString &filename, Scene *scene)
	 : IDrawable(scene)
{
	m_x = 0;
	m_y = 0;
	m_flipped = false;
	m_scene = scene;

	m_movie.setFileName(filename);
	m_movie.start();
}

float AnimatedSprite::x() const
{
	return m_x;
}

void AnimatedSprite::setX(const float x)
{
	m_x = x;
}

float AnimatedSprite::y() const
{
	return m_y;
}

void AnimatedSprite::setY(const float y)
{
	m_y = y;
}

bool AnimatedSprite::isFlipped()
{
	return m_flipped;
}

void AnimatedSprite::setFlipped(const bool flipped)
{
	m_flipped = flipped;
}

int AnimatedSprite::speed() const
{
	return m_movie.speed();
}

void AnimatedSprite::setSpeed(const int speed)
{
	m_movie.setSpeed(speed);
}

unsigned int AnimatedSprite::drawingOrder() const
{
	return 0;
}

QSGTexture *AnimatedSprite::texture()
{
	const int frame = m_movie.currentFrameNumber();
	const int frames = m_movie.frameCount();
	const int identifier = frame + frames * m_flipped;

	return m_textures.value(identifier) ?: createTexture(identifier);
}

QSGTexture *AnimatedSprite::createTexture(const int frame)
{
	QImage image = m_movie
		.currentImage()
		.mirrored(m_flipped, false);

	QSGTexture *texture = m_scene->createTexture(image);

	return m_textures
		.insert(frame, texture)
		.value();
}
