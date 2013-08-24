#include "Player.h"

#include "Bot.h"

Bot::Bot(const QPolygon &path, Scene *scene)
	: Actor("resources/guard.spb", scene),
	  m_path(path),
	  m_movingForward(true),
	  m_visionCone(this, scene)
{
	reloadPath();
}

float Bot::x() const
{
	return m_workPath.last().x2();
}

float Bot::y() const
{
	return m_workPath.last().y2();
}

void Bot::tick(const long delta)
{
	m_sprite.update(delta);

	qreal movement = 100.0f * (delta / 1000.0f);

	QLineF &currentLine = m_workPath.last();
	if(currentLine.length() - movement > 0)
	{
		currentLine.setLength(currentLine.length() - movement);
	}
	else if(m_workPath.count() > 1)
	{
		movement -= currentLine.length();
		m_workPath.removeLast();
		currentLine = m_workPath.last();
		currentLine.setLength(currentLine.length() - movement);
	}
	else
	{
		m_movingForward = !m_movingForward;
		reloadPath(!m_movingForward);
	}

	for(Player *player : m_trackedPlayers)
	{
//		if(m_visionCone.containsActor(*player))
//			qDebug() << "PLAYER SEEN!";
	}
}

void Bot::addPlayerTracking(Player *player)
{
	Q_ASSERT(!m_trackedPlayers.contains(player));
	m_trackedPlayers.append(player);
}

void Bot::reloadPath(bool reverse)
{
	m_workPath.clear();

	if(reverse)
	{
		for(int i = m_path.count() - 1; i > 0; i--)
			m_workPath.append(QLineF(m_path.at(i), m_path.at(i - 1)));
	}
	else
	{
		for(int i = 0; i < m_path.count() - 1; i++)
			m_workPath.append(QLineF(m_path.at(i), m_path.at(i + 1)));
	}

	m_flipped = (m_workPath.last().x1() < m_workPath.last().x2()) ? true : false;
}
