#include "Player.h"

#include "Bot.h"

Bot::Bot(const QPolygon &path, Scene *scene)
	: Actor("resources/guard.spb", scene),
	  m_currentLine(0),
	  m_positionInLine(0),
	  m_movingForward(true),
	  m_visionCone(this, scene)
{
	for(int i = 0; i < path.count() - 1; i++)
		m_path.append(QLineF(path.at(i), path.at(i + 1)));
}

float Bot::x() const
{
	return m_path.at(m_currentLine).pointAt(m_positionInLine).x();
}

float Bot::y() const
{
	return m_path.at(m_currentLine).pointAt(m_positionInLine).y();
}

void Bot::tick(const long delta)
{
	m_sprite.update(delta);
	m_flipped = m_movingForward;

	qreal movement = 100.0f * (delta / 1000.0f);
	if(!m_movingForward)
		movement = -movement;

	QLineF currentLine = m_path.at(m_currentLine);
	if(m_positionInLine + movement / currentLine.length() >= 0 && m_positionInLine + movement / currentLine.length() <= 1) // On-line movement
	{
		m_positionInLine += movement / currentLine.length();
	}
	else // Line transition
	{
		if(m_positionInLine + movement / currentLine.length() >= 1) // Next line in sequence
		{
			if(m_currentLine + 1 < m_path.count())
			{
				m_currentLine++;
				m_positionInLine = 0;
			}
			else
			{
				m_movingForward = !m_movingForward;
			}
		}
		else if(m_positionInLine + movement / currentLine.length() <= 0) // Previous line in sequence
		{
			if(m_currentLine > 0)
			{
				m_currentLine--;
				m_positionInLine = 1;
			}
			else
			{
				m_movingForward = !m_movingForward;
			}
		}

		movement -= movement * (movement / currentLine.length());
		m_positionInLine += movement / currentLine.length();
	}

	for(Player *player : m_trackedPlayers)
	{
		if(m_visionCone.containsActor(*player))
			player->respawn();
	}
}

void Bot::addPlayerTracking(Player *player)
{
	Q_ASSERT(!m_trackedPlayers.contains(player));
	m_trackedPlayers.append(player);
}
