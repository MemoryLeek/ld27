#include "Scene.h"

#include "Player.h"

Player::Player(Scene *scene)
	: Actor("resources/player.spb", scene),
	  m_velocity(0),
	  m_lastVelocity(0),
	  m_x(0),
	  m_y(0)
{

}

float Player::x() const
{
	return m_x;
}

float Player::y() const
{
	return m_y;
}

void Player::tick(const long delta)
{
	m_sprite.update(delta);
	m_x += m_velocity * (delta / 1000.0f);

	QSize playerSize = texture()->textureSize();
	QPointF playerCenter(playerSize.width() / 2, playerSize.height() / 2);
	m_scene->setCameraPosition(QPointF(m_x + playerCenter.x(), m_y + playerCenter.y()));
}

void Player::setVelocity(const float velocity)
{
	m_velocity = velocity;

	if(m_velocity != 0)
	{
		m_sprite.setImageIndex(Walking);
		m_flipped = m_velocity < 0 || (!m_velocity && m_lastVelocity < 0);
		m_lastVelocity = m_velocity;
	}
	else
	{
		m_sprite.setImageIndex(Idle);
	}
}
