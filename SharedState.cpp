#include "SharedState.h"

SharedState::SharedState()
{
	m_currentMap = 0;
	m_availableMaps =
	{
		"resources/maps/1.map",
		"resources/maps/2.map",
		"resources/maps/3.map"
	};
}

QStringList SharedState::availableMaps() const
{
	return m_availableMaps;
}

QString SharedState::currentMap() const
{
	return m_availableMaps[m_currentMap];
}

void SharedState::nextMap()
{
	m_currentMap++;
}

void SharedState::previousMap()
{
	m_currentMap--;
}
