#include "LogoState.h"
#include "QTimerEx.h"

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
		/* No implementation */
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
		m_skipping = true;

		killTimer(m_timerId);
		changeState<States::GameState>();
	}
}
