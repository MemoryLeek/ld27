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
#include "SharedState.h"

namespace States
{
	DummyState::DummyState()
	{
		m_player = 0;
		m_fpsTimer = 0;
		m_lastFps = 0;
		m_reverseTime = false;
		m_timePool = 10;
		m_scene = 0;
		m_joystick = 0;

		m_timer.start();

		setFlag(QQuickItem::ItemHasContents);
		setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
	}

	QString DummyState::fps() const
	{
		return QStringEx::format("%1 FPS", m_lastFps);
	}

	float DummyState::timePool() const
	{
		return m_timePool;
	}

	QSGNode *DummyState::updatePaintNode(QSGNode *, QQuickItem::UpdatePaintNodeData *)
	{
		int delta = m_timer.restart();

		m_scene->markDirty(QSGNode::DirtyForceUpdate);
		m_player->tick(delta);
		m_fps++;

		if((m_fpsTimer += delta) >= 1000)
		{
			emit fpsChanged();

			m_lastFps = m_fps;
			m_fpsTimer = 0;
			m_fps = 0;
		}

		if(m_reverseTime && m_timePool > 0)
		{
			m_timePool -= delta / 1000.f;
			emit timePoolChanged();
			delta = -delta;
		}

		if(!m_reverseTime && m_timePool < 10)
		{
			m_timePool += delta / 1000.f;
			if(m_timePool > 10)
				m_timePool = 10;
			emit timePoolChanged();
		}

		for(Bot *bot : m_bots)
		{
			bot->tick(delta);
		}

		processJoystick();
		update();

		return m_scene;
	}

	void DummyState::initialize()
	{
		initializeScene();
		initializeJoystick();
	}

	void DummyState::complete()
	{
		/* No implementation */
	}

	void DummyState::keyPressEvent(QKeyEvent *event)
	{
		if(!event->isAutoRepeat())
		{
			switch(event->key())
			{
				case Qt::Key_Left:
				case Qt::Key_A:
				{
					m_player->setDirection(-1);
					m_player->setVelocity(500);

					break;
				}

				case Qt::Key_Right:
				case Qt::Key_D:
				{
					m_player->setDirection(1);
					m_player->setVelocity(500);

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

				case Qt::Key_Return:
				{
					m_player->respawn();
					break;
				}
			}
		}
	}

	void DummyState::keyReleaseEvent(QKeyEvent *event)
	{
		if(!event->isAutoRepeat())
		{
			switch(event->key())
			{
				case Qt::Key_Left:
				case Qt::Key_A:
				{
					m_player->setDirection(0);
					break;
				}

				case Qt::Key_Right:
				case Qt::Key_D:
				{
					m_player->setDirection(0);
					break;
				}

				case Qt::Key_Control:
				{
					m_reverseTime = false;
					break;
				}
			}
		}
	}

	void DummyState::mousePressEvent(QMouseEvent *event)
	{
		switch(event->button())
		{
			case Qt::LeftButton:
			{
				m_reverseTime = true;
				break;
			}

			case Qt::RightButton:
			{
				m_player->jump();
				break;
			}

			default:
			{
				break;
			}
		}
	}

	void DummyState::mouseReleaseEvent(QMouseEvent *event)
	{
		switch(event->button())
		{
			case Qt::LeftButton:
			{
				m_reverseTime = false;
				break;
			}

			default:
			{
				break;
			}
		}
	}

	void DummyState::joystickEvent(const JoystickEvent &event)
	{
		if((m_lastJoystickEvent.buttons() & JoystickEvent::ButtonJump) != (event.buttons() & JoystickEvent::ButtonJump))
		{
			if(!(m_lastJoystickEvent.buttons() & JoystickEvent::ButtonJump))
				m_player->jump();
		}
		if((m_lastJoystickEvent.buttons() & JoystickEvent::ButtonRestart) != (event.buttons() & JoystickEvent::ButtonRestart))
		{
			if(!(m_lastJoystickEvent.buttons() & JoystickEvent::ButtonRestart))
				m_player->respawn();
		}
		if((m_lastJoystickEvent.buttons() & JoystickEvent::ButtonReverseTime) != (event.buttons() & JoystickEvent::ButtonReverseTime))
		{
			m_reverseTime = (m_lastJoystickEvent.buttons() & JoystickEvent::ButtonReverseTime) ? false : true;
		}


		if(event.axis().x() == 0)
		{
			m_player->setDirection(0);
		}
		else
		{
			m_player->setDirection(event.axis().x() / abs(event.axis().x()));
			m_player->setVelocity(abs(event.axis().x()) * 5);
		}

		m_lastJoystickEvent = event;
	}

	void DummyState::processJoystick()
	{
		if(m_joystick)
		{
			SDL_JoystickUpdate();

			float x = SDL_JoystickGetAxis(m_joystick, 0) / 300.f;
			float y = SDL_JoystickGetAxis(m_joystick, 1) / 300.f;

			// Deadzone
			if(x > -10 && x < 10)
				x = 0;
			if(y > -10 && y < 10)
				y = 0;

			// Limits
			if(x > 100)
				x = 100;
			if(x < -100)
				x = -100;
			if(y > 100)
				y = 100;
			if(y < -100)
				y = -100;

			JoystickEvent::Buttons buttons = JoystickEvent::ButtonNone;
			if(SDL_JoystickGetButton(m_joystick, 0))
				buttons |= JoystickEvent::ButtonJump;
			if(SDL_JoystickGetButton(m_joystick, 2))
				buttons |= JoystickEvent::ButtonReverseTime;
			if(SDL_JoystickGetButton(m_joystick, 3))
				buttons |= JoystickEvent::ButtonRestart;

			JoystickEvent jsEvent(QVector2D(x, y), buttons);
			if(jsEvent != m_lastJoystickEvent)
			{
				joystickEvent(jsEvent);
				m_lastJoystickEvent = jsEvent;
			}
		}
	}

	void DummyState::initializeScene()
	{
		Window *window = getComponent<Window>();
		SharedState *state = getComponent<SharedState>();
		Scene *scene = new Scene(window);

		MapLoader mapLoader(scene);
		Map *map = mapLoader.load("resources/maps/2.map");
		map->initialize(scene);

		m_scene = scene;
		m_player = new Player(map, scene);

		const QList<QPolygon> &paths = map->paths();

		for(const QPolygon &path : paths)
		{
			Bot *bot = new Bot(path, map, scene);
			bot->addPlayerTracking(m_player);

			m_bots << bot;
		}
	}

	void DummyState::initializeJoystick()
	{
		if(SDL_NumJoysticks() > 0)
		{
			qDebug() << "Opening joystick 0";
			m_joystick = SDL_JoystickOpen(0);
		}
	}
}
