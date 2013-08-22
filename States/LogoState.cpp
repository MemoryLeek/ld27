#include "LogoState.h"
#include "QTimerEx.h"

#include "States/DummyState.h"

namespace States
{
	LogoState::LogoState()
		: m_skipping(false)
	{
		QTimerEx::singleShot(4000, this, &LogoState::skip);
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

		changeState<States::DummyState>();
	}
}
