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
	  m_isOnGround(false),
	  m_map(map),
	  m_stepSoundTimer(0)
{
	m_jumpSound.setSource(QUrl::fromLocalFile("resources/sound/jump.wav"));
	m_jumpSound.setVolume(0.5);
	m_stepSound.setSource(QUrl::fromLocalFile("resources/sound/step.wav"));
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
	float x = m_x + (m_xThrust * m_xVelocity) * (delta / 1000.0f);
	float y = m_y + (m_yThrust * m_yVelocity) * (delta / 1000.0f);

	const QSGTexture *t = texture();
	const QSize playerSize = t->textureSize();
	const QPointF playerCenter(playerSize.width() / 2, playerSize.height() / 2);
	const QPointF cameraPosition(m_x + playerCenter.x(), m_y + playerCenter.y());

	m_sprite.update(delta);
	m_scene->setCameraPosition(cameraPosition, m_map);

	m_isOnGround = false;
	for(const QPolygonF &collidable : m_map->collidables())
	{
		// Check left collision
		for(int i = y + 6; i < y + playerSize.height() - 6; i++)
		{
			while(collidable.containsPoint(QPointF(x + 4, i), Qt::OddEvenFill))
			{
				x++;
			}
		}

		// Check right collision
		for(int i = y + 6; i < y + playerSize.height() - 6; i++)
		{
			while(collidable.containsPoint(QPointF(x + playerSize.width() - 4, i), Qt::OddEvenFill))
			{
				x--;
			}
		}

		// Check top collision
		for(int i = x + 6; i < x + playerSize.width() - 6; i++)
		{
			while(collidable.containsPoint(QPointF(i, y + 1), Qt::OddEvenFill))
			{
				y++;
				m_yVelocity = 100;
			}
		}

		// Check bottom collision
		for(int i = m_x + 6; i < m_x + playerSize.width() - 6; i++)
		{
			while(collidable.containsPoint(QPointF(i, y + playerSize.height() - 2), Qt::OddEvenFill))
			{
				y--;
				if(m_yVelocity > 0)
					m_yVelocity = 0;
			}

			if(collidable.containsPoint(QPointF(i, y + playerSize.height() - 1), Qt::OddEvenFill))
			{
				m_isOnGround = true;
			}
		}
	}

	if(m_isOnGround && m_x != x)
	{
		m_stepSoundTimer += delta;
		if(m_stepSoundTimer > 250)
		{
			m_stepSound.play();
			m_stepSoundTimer = 0;
		}
	}

	if(!m_isOnGround && m_yVelocity == 0)
	{
		m_yVelocity = 100;
	}

	if(m_yVelocity > 100)
	{
		m_yVelocity -= delta / 2.0f;
	}
	else
	{
		m_yThrust = 1;
	}

	m_x = x;
	m_y = y;
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
	if(!m_isOnGround)
		return;

	m_jumpSound.play();
	m_yThrust = -1;
	m_yVelocity = 300;
}

void Player::respawn()
{
	m_x = m_map->spawnPoint().x();
	m_y = m_map->spawnPoint().y();
}
