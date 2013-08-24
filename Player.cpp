#include "Scene.h"
#include "Map.h"

#include "Player.h"

Player::Player(Map *map, Scene *scene)
	: Actor("resources/player.spb", scene),
	  m_velocity(0),
	  m_lastVelocity(0),
	  m_x(0),
	  m_y(0),
	  m_map(map)
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
	QSize mapSize = m_map->texture()->textureSize();
	if(m_x < 0)
		m_x = 0;
	if(m_x + playerSize.width() > mapSize.width())
		m_x = mapSize.width() - playerSize.width();
	if(m_y < 0)
		m_y = 0;
	if(m_y + playerSize.height() > mapSize.height())
		m_y = mapSize.height() - playerSize.height();

	QPointF playerCenter(playerSize.width() / 2, playerSize.height() / 2);
	m_scene->setCameraPosition(QPointF(m_x + playerCenter.x(), m_y + playerCenter.y()), m_map);
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
