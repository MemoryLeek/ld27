#include "LogoState.h"
#include "QTimerEx.h"
#include "StateHandler.h"

#include "States/GameState.h"

namespace States
{
	LogoState::LogoState()
	{
		m_skipping = false;
		m_timerId = startTimer(4000);
	}

	void LogoState::initialize()
	{
		m_stateHandler = getComponent<StateHandler>();
	}

	void LogoState::complete()
	{
		/* No implementation */
	}

	void LogoState::timerEvent(QTimerEvent *)
	{
		skip();
	}

	void LogoState::keyPressEvent(QKeyEvent *)
	{
		if(!m_skipping)
		{
			skip();
		}
	}

	void LogoState::skip()
	{
		killTimer(m_timerId);

		m_skipping = true;
		m_stateHandler->changeState<States::GameState>();
	}
}
