#include <qmath.h>

#include "GameState.h"
#include "QStringEx.h"
#include "Key.h"
#include "Direction.h"
#include "Scene.h"
#include "Player.h"
#include "Bot.h"
#include "MapLoader.h"
#include "Map.h"
#include "SharedState.h"
#include "FrameDrawingContext.h"
#include "Compositor.h"

namespace States
{
	GameState::GameState()
	{
		m_player = 0;
		m_fpsTimer = 0;
		m_lastFps = 0;
		m_reverseTime = false;
		m_timePool = 10;
		m_scene = 0;
		m_joystick = 0;
		m_window = 0;
		m_map = 0;

		m_timer.start();

		setFlag(QQuickItem::ItemHasContents);
		setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
	}

	QString GameState::fps() const
	{
		return QStringEx::format("%1 FPS", m_lastFps);
	}

	float GameState::timePool() const
	{
		return m_timePool;
	}

	void GameState::paint(QPainter *painter)
	{
		const QRect &rect = painter->window();
		const QSize &size = rect.size();

		FrameDrawingContext *context = new FrameDrawingContext(size);

		int delta = m_timer.restart();

		const int width = m_window->width();
		const int height = m_window->height();
		const int cx = qMax(0.0f, m_player->x() - (width / 2));
		const int cy = qMax(0.0f, m_player->y() - (height / 2));

		m_map->draw(context, cx, cy, delta);
		m_player->draw(context, cx, cy, delta);

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
			bot->draw(context, cx, cy, delta);
		}

		m_compositor->composite(context, painter);
		m_fps++;

		processJoystick();
		update();
	}

	void GameState::initialize()
	{
		initializeScene();
		initializeJoystick();
	}

	void GameState::complete()
	{
		/* No implementation */
	}

	void GameState::keyPressEvent(QKeyEvent *event)
	{
		if(!event->isAutoRepeat())
		{
			switch(event->key())
			{
				case Qt::Key_Left:
				case Qt::Key_A:
				{
					m_player->setDirection(-1);
					m_player->setVelocity(200);

					break;
				}

				case Qt::Key_Right:
				case Qt::Key_D:
				{
					m_player->setDirection(1);
					m_player->setVelocity(200);

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

	void GameState::keyReleaseEvent(QKeyEvent *event)
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

	void GameState::mousePressEvent(QMouseEvent *event)
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

	void GameState::mouseReleaseEvent(QMouseEvent *event)
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

	void GameState::joystickEvent(const JoystickEvent &event)
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
			m_player->setVelocity(abs(event.axis().x()) * 2);
		}

		m_lastJoystickEvent = event;
	}

	void GameState::processJoystick()
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

	void GameState::initializeScene()
	{
		Window *window = getComponent<Window>();
		SharedState *state = getComponent<SharedState>();
		Compositor *compositor = getComponent<Compositor>();
		Scene *scene = new Scene(window);

		QString filename = state->currentMap();

		MapLoader mapLoader(scene);
		Map *map = mapLoader.load(filename);
		map->initialize();

		m_scene = scene;
		m_compositor = compositor;
		m_window = window;
		m_player = new Player(map, scene, window);
		m_map = map;

		const QList<QPolygon> &paths = map->paths();

		for(const QPolygon &path : paths)
		{
			Bot *bot = new Bot(path, map);
			bot->addPlayerTracking(m_player);

			m_bots << bot;
		}
	}

	void GameState::initializeJoystick()
	{
		if(SDL_NumJoysticks() > 0)
		{
			qDebug() << "Opening joystick 0";
			m_joystick = SDL_JoystickOpen(0);
		}
	}
}
