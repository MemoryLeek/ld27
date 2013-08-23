#include <qmath.h>

#include "DummyState.h"
#include "QStringEx.h"
#include "Key.h"
#include "Direction.h"
#include "Scene.h"
#include "AnimatedSprite.h"

namespace States
{
	DummyState::DummyState()
	{
		m_x = 0;
		m_y = 0;
		m_direction = 0;
		m_velocity = 0;
		m_fpsTimer = 0;
		m_lastFps = 0;
		m_sprite = 0;
	}

	QString DummyState::fps() const
	{
		return QStringEx::format("%1 FPS", m_lastFps);
	}

	void DummyState::initialize(Scene *scene)
	{
		m_sprite = new AnimatedSprite("resources/lone-walking.gif", scene);
	}

	void DummyState::tick(long delta)
	{
		const float multiplier = delta / 1000.0f;
		const float x = m_x + qCos(m_direction * M_PI / 180) * multiplier * m_velocity;
		const float y = m_y + qSin(m_direction * M_PI / 180) * multiplier * m_velocity;

		m_sprite->setX(x);
		m_sprite->setY(y);

		m_fps++;
		m_x = x;
		m_y = y;

		if((m_fpsTimer += delta) >= 1000)
		{
			emit fpsChanged();

			m_lastFps = m_fps;
			m_fpsTimer = 0;
			m_fps = 0;
		}
	}

	void DummyState::keyPressed(QKeyEvent *event)
	{
		switch(event->key())
		{
			case Qt::Key_W:
			{
				m_keyStates << Key::KeyUp;
				break;
			}

			case Qt::Key_S:
			{
				m_keyStates << Key::KeyDown;
				break;
			}

			case Qt::Key_A:
			{
				m_keyStates << Key::KeyLeft;
				m_sprite->setFlipped(true);

				break;
			}

			case Qt::Key_D:
			{
				m_keyStates << Key::KeyRight;
				m_sprite->setFlipped(false);

				break;
			}
		}

		updatePlayerMovement();
	}

	void DummyState::keyReleased(QKeyEvent *event)
	{
		switch(event->key())
		{
			case Qt::Key_W:
			{
				m_keyStates.removeAll(Key::KeyUp);
				break;
			}

			case Qt::Key_S:
			{
				m_keyStates.removeAll(Key::KeyDown);
				break;
			}

			case Qt::Key_A:
			{
				m_keyStates.removeAll(Key::KeyLeft);
				break;
			}

			case Qt::Key_D:
			{
				m_keyStates.removeAll(Key::KeyRight);
				break;
			}
		}

		updatePlayerMovement();
	}

	void DummyState::updatePlayerMovement()
	{
		if(!m_keyStates.isEmpty())
		{
			const int key = m_keyStates.last();
			const int direction = Direction::fromKey(key);

			m_direction = direction;
			m_velocity = 100;
		}
		else
		{
			m_direction = 0;
			m_velocity = 0;
		}
	}
}
