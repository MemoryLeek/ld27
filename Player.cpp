#include "Scene.h"
#include "Map.h"

#include "Player.h"

Player::Player(Map *map, Scene *scene)
	: Actor("resources/player.spb", scene),
	  m_xVelocity(500),
	  m_yVelocity(100),
	  m_xThrust(0),
	  m_yThrust(1),
	  m_lastDirection(0),
	  m_x(200),
	  m_y(1400),
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
	const float x = m_x + (m_xThrust * m_xVelocity) * (delta / 1000.0f);
	const float y = m_y + (m_yThrust * m_yVelocity) * (delta / 1000.0f);

	const QSGTexture *t = texture();
	const QSize playerSize = t->textureSize();
	const QPointF playerCenter(playerSize.width() / 2, playerSize.height() / 2);
	const QPointF cameraPosition(m_x + playerCenter.x(), m_y + playerCenter.y());

	m_sprite.update(delta);
	m_scene->setCameraPosition(cameraPosition, m_map);

	const QLineF lx(m_x, m_y, x, m_y);
	const QLineF ly(m_x, m_y, m_x, y);

	if(lx.length() > 0)
	{
		int i = 0;

		for(; i <= lx.length(); i++)
		{
			const int rx = m_x + (i * m_xThrust) + playerSize.width() * (m_xThrust > 0);
			const int ry = y + playerSize.height() * (m_yThrust > 0);

			const bool isCollidable = m_map->isCollidable(rx, ry);

			if(isCollidable)
			{
				break;
			}
		}

		if(i > lx.length())
		{
			m_x = x;
		}
	}

	if(ly.length() > 0)
	{
		int i = 0;

		for(; i <= ly.length(); i++)
		{
			const int rx = x + playerSize.width() * (m_xThrust > 0);
			const int ry = m_y + ((i - 1) * m_yThrust) + playerSize.height() * (m_yThrust > 0);

			const bool isCollidable = m_map->isCollidable(rx, ry);

			if(isCollidable)
			{
				break;
			}
		}

		if(i > ly.length())
		{
			m_y = y;
		}
	}

	if(m_yVelocity > 100)
	{
		m_yVelocity -= delta / 2.0f;
	}
	else
	{
		m_yThrust = 1;
	}

//	if(m_x < 0)
//	{
//		m_x = 0;
//	}

//	if(m_x + playerSize.width() > m_map->width())
//	{
//		m_x = m_map->width() - playerSize.width();
//	}

//	if(m_y < 0)
//	{
//		m_y = 0;
//	}

//	if(m_y + playerSize.height() > m_map->height())
//	{
//		m_y = m_map->height() - playerSize.height();
//	}


}

void Player::setVelocity(const float velocity)
{
	m_xVelocity = velocity;
}

void Player::setDirection(const float direction)
{
	m_xThrust = direction;

	if(m_xThrust != 0)
	{
		m_sprite.setImageIndex(Walking);
		m_flipped = m_xThrust < 0 || (!m_xThrust && m_xThrust < 0);
		m_lastDirection = m_xThrust;
	}
	else
	{
		m_sprite.setImageIndex(Idle);
	}
}

void Player::jump()
{
	m_yThrust = -1;
	m_yVelocity = 300;
}
