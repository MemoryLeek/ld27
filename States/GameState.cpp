#include "GameState.h"
#include "Window.h"
#include "Scene.h"

namespace States
{
	GameState::GameState()
	{
		m_scene = 0;
		m_timer.start();

		setFlag(QQuickItem::ItemHasContents);
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

			initialize(m_scene);
			update();
		}
		else
		{
			m_scene->markDirty(QSGNode::DirtyForceUpdate);

			const long delta = m_timer.restart();

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
