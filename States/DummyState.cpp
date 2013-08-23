#include <qmath.h>

#include "DummyState.h"
#include "QStringEx.h"
#include "Key.h"
#include "Direction.h"

namespace States
{
	DummyState::DummyState()
		: m_x(0)
		, m_y(0)
		, m_direction(0)
		, m_velocity(0)
		, m_fpsTimer(0)
		, m_lastFps(0)
	{
		m_node = new QSGSimpleRectNode();
		m_node->setColor(Qt::red);
		m_node->setRect(0, 0, 10, 10);

		m_timer.start();

		setFlag(QQuickItem::ItemHasContents);
	}

	QString DummyState::fps() const
	{
		return QStringEx::format("%1 FPS", m_lastFps);
	}

	QSGNode *DummyState::updatePaintNode(QSGNode *, QQuickItem::UpdatePaintNodeData *)
	{
		const float delta = m_timer.restart() / 1000.0f;
		const float x = m_x + qCos(m_direction * M_PI / 180) * delta * m_velocity;
		const float y = m_y + qSin(m_direction * M_PI / 180) * delta * m_velocity;

		m_node->setRect(m_x, m_y, 10, 10);
		m_fps++;
		m_x = x;
		m_y = y;

		if((m_fpsTimer += delta) >= 1)
		{
			emit fpsChanged();

			m_lastFps = m_fps;
			m_fps = 0;
			m_fpsTimer = 0;
		}

		update();

		return m_node;
	}

	void DummyState::keyPressEvent(QKeyEvent *event)
	{
		if(!event->isAutoRepeat())
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
					break;
				}

				case Qt::Key_D:
				{
					m_keyStates << Key::KeyRight;
					break;
				}
			}

			updatePlayerMovement();
		}
	}

	void DummyState::keyReleaseEvent(QKeyEvent *event)
	{
		if(!event->isAutoRepeat())
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
