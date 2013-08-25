#include <SDL2/SDL.h>

#include "GameState.h"
#include "Window.h"
#include "Scene.h"

namespace States
{
	GameState::GameState()
	{
		m_scene = 0;
		m_timer.start();
		m_joystick = NULL;

		setFlag(QQuickItem::ItemHasContents);
		setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
	}

	GameState::~GameState()
	{
		delete m_scene;
	}

	QSGNode *GameState::updatePaintNode(QSGNode *, QQuickItem::UpdatePaintNodeData *)
	{
		if(!m_scene)
		{
			Window *window = getComponent<Window>();
			Scene *scene = new Scene(window);

			m_scene = scene;

			if(SDL_NumJoysticks() > 0)
			{
				qDebug() << "Opening joystick 0";
				m_joystick = SDL_JoystickOpen(0);
			}

			initialize(m_scene);
			update();
		}
		else
		{
			m_scene->markDirty(QSGNode::DirtyForceUpdate);

			const long delta = m_timer.restart();

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

			tick(delta);
			update();
		}

		return m_scene;
	}

	void GameState::keyPressEvent(QKeyEvent *event)
	{
		if(!event->isAutoRepeat())
		{
			keyPressed(event);
		}
	}

	void GameState::keyReleaseEvent(QKeyEvent *event)
	{
		if(!event->isAutoRepeat())
		{
			keyReleased(event);
		}
	}
}
