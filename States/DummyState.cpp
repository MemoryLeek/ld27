#include <qmath.h>

#include "DummyState.h"
#include "QStringEx.h"
#include "Key.h"
#include "Direction.h"
#include "Scene.h"
#include "Player.h"
#include "Bot.h"
#include "MapLoader.h"

namespace States
{
	DummyState::DummyState()
	{
		m_fpsTimer = 0;
		m_lastFps = 0;
		m_player = 0;
	}

	QString DummyState::fps() const
	{
		return QStringEx::format("%1 FPS", m_lastFps);
	}

	void DummyState::initialize(Scene *scene)
	{
		MapLoader mapLoader(scene);
		Map *map = mapLoader.load("resources/maps/1.map");

		m_player = new Player(scene);

		m_bots.append(new Bot(QPolygon(QVector<QPoint>({QPoint(100, 0), QPoint(300, 0), QPoint(500, 200)})), scene));
		m_bots.last()->addPlayerTracking(m_player);
		m_bots.append(new Bot(QPolygon(QVector<QPoint>({QPoint(500, 400), QPoint(200, 400)})), scene));
		m_bots.last()->addPlayerTracking(m_player);
	}

	void DummyState::tick(long delta)
	{
		m_player->tick(delta);
		for(Bot *bot : m_bots)
			bot->tick(delta);
		m_fps++;

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
				m_player->setVelocity(-100);
//				m_keyStates << Key::KeyLeft;
				break;
			}

			case Qt::Key_D:
			{
				m_player->setVelocity(100);
//				m_keyStates << Key::KeyRight;
				break;
			}
		}

//		updatePlayerMovement();
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
				m_player->setVelocity(0);
//				m_keyStates.removeAll(Key::KeyLeft);
				break;
			}

			case Qt::Key_D:
			{
				m_player->setVelocity(0);
//				m_keyStates.removeAll(Key::KeyRight);
				break;
			}
		}

//		updatePlayerMovement();
	}

	void DummyState::updatePlayerMovement()
	{
//		if(!m_keyStates.isEmpty())
//		{
//			const int key = m_keyStates.last();
//			const int direction = Direction::fromKey(key);

//			m_direction = direction;
//			m_velocity = 100;
//		}
//		else
//		{
//			m_direction = 0;
//			m_velocity = 0;
//		}
	}
}
