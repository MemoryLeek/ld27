#include <QPainter>

#include "Player.h"
#include "Bot.h"
#include "SpriteLoader.h"
#include "VisionConeDrawable.h"
#include "FrameDrawingContext.h"
#include "Surface.h"

Bot::Bot(const QPolygon &path, Map *map)
{
	SpriteLoader spriteLoader;
	SpriteBundle sprite = spriteLoader.load("resources/guard.spb");

	m_sprite = sprite;
	m_map = map;
	m_currentLine = 0;
	m_positionInLine = 0;
	m_movingForward = true;
	//	  m_directionSwitchDelay(0),
	m_visionCone = new VisionConeDrawable(this, map);
	m_flipped = false;

	for(int i = 0; i < path.count() - 1; i++)
	{
		m_path.append(QLineF(path.at(i), path.at(i + 1)));
	}

//	m_alarmSound.setSource(QUrl::fromLocalFile("resources/sound/alarm.wav"));
//	m_alarmSound.setLoopCount(3);
}

float Bot::x() const
{
	return m_path.at(m_currentLine).pointAt(m_positionInLine).x();
}

float Bot::y() const
{
	return m_path.at(m_currentLine).pointAt(m_positionInLine).y();
}

unsigned int Bot::drawingOrder() const
{
	return 1;
}

void Bot::draw(FrameDrawingContext &context, const int cx, const int cy, const int delta)
{
//	if(m_directionSwitchDelay <= 0) // Don't flip direction when we're idling
//	{
		m_sprite.update(delta);
		m_flipped = m_movingForward;
//	}

	qreal movement = 100.0f * (delta / 1000.0f);
	if(!m_movingForward)
		movement = -movement;

	QLineF currentLine = m_path.at(m_currentLine);
//	if(m_directionSwitchDelay >= 0)
//	{
//		m_directionSwitchDelay -= delta;
//	}
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
				m_positionInLine = 1;
//				m_directionSwitchDelay = 1500;
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
				m_positionInLine = 0;
//				m_directionSwitchDelay = 1500;
			}
		}

		m_positionInLine += movement / currentLine.length();
	}

	for(Player *player : m_trackedPlayers)
	{
		if(m_visionCone->containsActor(*player))
		{
//			if(!m_alarmSound.isPlaying())
//				m_alarmSound.play();
			player->respawn();
		}
	}

	m_visionCone->draw(context, cx, cy, delta);

	const QImage &m = m_sprite.currentImage(m_flipped);
	const QPoint cameraPosition(cx, cy);
	const QPoint position(x(), y());
	const QPoint adjusted = position - cameraPosition;

	Surface &surface = context.background();
	QPainter painter(&surface);

	painter.drawImage(adjusted, m);
}

void Bot::addPlayerTracking(Player *player)
{
	Q_ASSERT(!m_trackedPlayers.contains(player));
	m_trackedPlayers.append(player);
}

bool Bot::isFlipped() const
{
	return m_flipped;
}
