#include <QGuiApplication>
#include <QPainter>

#include "Scene.h"
#include "Map.h"
#include "Window.h"
#include "SharedState.h"
#include "FrameDrawingContext.h"
#include "Player.h"
#include "SpriteLoader.h"
#include "Surface.h"

Player::Player(Map *map, Scene *scene, Window *window)
{
	const QPoint &p = map->spawnPoint();

	SpriteLoader spriteLoader;
	SpriteBundle sprite = spriteLoader.load("resources/player.spb");

	m_sprite = sprite;
	m_xVelocity = 0;
	m_yVelocity = 100;
	m_xThrust = 0;
	m_yThrust = 1;
	m_lastDirection = 0;
	m_isOnGround = false;
	m_flipped = false;
	m_map = map;
	m_window = window;
	m_x = p.x();
	m_y = p.y();
	m_scene = scene;
//	m_jumpSound.setSource(QUrl::fromLocalFile("resources/sound/jump.wav"));
//	m_jumpSound.setVolume(0.5);
//	m_stepSound.setSource(QUrl::fromLocalFile("resources/sound/step.wav"));
}

float Player::x() const
{
	return m_x;
}

float Player::y() const
{
	return m_y;
}

int Player::width() const
{
	return 32;
}

int Player::height() const
{
	return 64;
}

unsigned int Player::drawingOrder() const
{
	return 1;
}

void Player::draw(FrameDrawingContext &context, const int cx, const int cy, const int delta)
{
	float x = m_x + (m_xThrust * m_xVelocity) * (delta / 1000.0f);
	float y = m_y + (m_yThrust * m_yVelocity) * (delta / 1000.0f);

//	QPainter painter(surface);

	const QImage &texture = m_sprite.currentImage(m_flipped);
	const QSize playerSize = texture.size();
	const QRectF playerBoundingBox(x, y, playerSize.width(), playerSize.height());
	const QRect &goal = m_map->goal();

	if(m_isOnGround)
	{
		if(m_xThrust)
			m_sprite.setImageIndex(Walking);
		else
			m_sprite.setImageIndex(Idle);
	}
	else
	{
		if(m_yThrust < 0)
			m_sprite.setImageIndex(Jumping);
		else
			m_sprite.setImageIndex(Falling);
	}

	m_sprite.update(delta);
	m_isOnGround = false;

	for(const Collidable &collidable : m_map->collidables())
	{
		const QPolygonF &polygon = collidable.polygon();
		const QRectF &boundingBox = collidable.boundingBox();

		if(boundingBox.intersects(playerBoundingBox))
		{
			// Check bottom collision
			for(int i = m_x + 6; i < m_x + playerSize.width() - 6; i += 2)
			{
				while(polygon.containsPoint(QPointF(i, y + playerSize.height() - 2), Qt::OddEvenFill))
				{
					y--;
					if(m_yVelocity > 0)
						m_yVelocity = 0;
				}

				if(!m_isOnGround && polygon.containsPoint(QPointF(i, y + playerSize.height() - 1), Qt::OddEvenFill))
				{
					m_isOnGround = true;
				}
			}

			// Check left collision
			for(int i = y + 6; i < y + playerSize.height() - 6; i += 2)
			{
				while(polygon.containsPoint(QPointF(x + 4, i), Qt::OddEvenFill))
				{
					x++;
				}
			}

			// Check right collision
			for(int i = y + 6; i < y + playerSize.height() - 6; i += 2)
			{
				while(polygon.containsPoint(QPointF(x + playerSize.width() - 4, i), Qt::OddEvenFill))
				{
					x--;
				}
			}

			// Check top collision
			for(int i = x + 6; i < x + playerSize.width() - 6; i += 2)
			{
				while(polygon.containsPoint(QPointF(i, y + 1), Qt::OddEvenFill))
				{
					y++;
					m_yVelocity = 100;
				}
			}
		}
	}

	if(m_isOnGround && m_x != x)
	{
		m_stepSoundTimer += delta;
		if(m_stepSoundTimer > 250)
		{
//			m_stepSound.play();
			m_stepSoundTimer = 0;
		}
	}

	if(!m_isOnGround && m_yThrust > 0)
	{
		m_yVelocity += delta / 3.0f;
		if(m_yVelocity > 1000)
			m_yVelocity = 1000;
	}

	if(m_yThrust < 0 && m_yVelocity > 100)
	{
		m_yVelocity -= delta / 2.0f;
	}
	else
	{
		m_yThrust = 1;
	}

	bool reachedGoal = goal.contains(x, y);

	if(reachedGoal)
	{
		m_window->setActiveState("GoalState");
	}

	m_x = x;
	m_y = y;

	QPoint position(m_x, m_y);
	QPoint cameraPosition(cx, cy);
	QPoint adjusted = position - cameraPosition;

	Surface &m = context.background(); //texture, m_x - cx, m_y - cy,
	QPainter painter(&m);
	painter.drawImage(adjusted, texture);
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

//	m_jumpSound.play();
	m_yThrust = -1;
	m_yVelocity = 323;
}

void Player::respawn()
{
	m_window->setActiveState("DeathState");

//	m_x = m_map->spawnPoint().x();
//	m_y = m_map->spawnPoint().y();
}
