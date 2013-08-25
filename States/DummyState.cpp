#include <qmath.h>

#include "DummyState.h"
#include "QStringEx.h"
#include "Key.h"
#include "Direction.h"
#include "Scene.h"
#include "Player.h"
#include "Bot.h"
#include "MapLoader.h"
#include "Map.h"

namespace States
{
	DummyState::DummyState()
	{
		m_player = 0;
		m_fpsTimer = 0;
		m_lastFps = 0;
		m_reverseTime = false;
	}

	QString DummyState::fps() const
	{
		return QStringEx::format("%1 FPS", m_lastFps);
	}

	void DummyState::initialize(Scene *scene)
	{
		MapLoader mapLoader(scene);
		Map *map = mapLoader.load("resources/maps/1.map");
		map->initialize(scene);

		m_player = new Player(map, scene);

		const QList<QPolygon> &paths = map->paths();

		for(const QPolygon &path : paths)
		{
			qDebug() << "path";

			Bot *bot = new Bot(path, scene);
			bot->addPlayerTracking(m_player);

			m_bots << bot;
		}
	}

	void DummyState::tick(long delta)
	{
		if(m_reverseTime)
			delta = -delta;

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
				m_player->setDirection(-1);
//				m_keyStates << Key::KeyLeft;
				break;
			}

			case Qt::Key_D:
			{
				m_player->setDirection(1);
//				m_keyStates << Key::KeyRight;
				break;
			}

			case Qt::Key_Space:
			{
				m_player->jump();
				break;
			}

			case Qt::Key_Control:
			{
				m_reverseTime = true;
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
				m_player->setDirection(0);
//				m_keyStates.removeAll(Key::KeyLeft);
				break;
			}

			case Qt::Key_D:
			{
				m_player->setDirection(0);
//				m_keyStates.removeAll(Key::KeyRight);
				break;
			}

			case Qt::Key_Control:
			{
				m_reverseTime = false;
				break;
			}
		}

//		updatePlayerMovement();
	}

	void DummyState::joystickEvent(const JoystickEvent &event)
	{
		if((m_lastJoystickEvent.buttons() & JoystickEvent::ButtonJump) != (event.buttons() & JoystickEvent::ButtonJump))
		{
			if(m_lastJoystickEvent.buttons() & JoystickEvent::ButtonJump)
				m_player->jump();
		}

		m_player->setDirection(event.axis().x() / abs(event.axis().x()));
		m_player->setVelocity(abs(event.axis().x()));

		m_lastJoystickEvent = event;
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
