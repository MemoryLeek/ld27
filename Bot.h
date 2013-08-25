#ifndef BOT_H
#define BOT_H

#include <QSoundEffect>

#include "VisionConeDrawable.h"

#include "Actor.h"

class Player;
class Map;

class Bot : public Actor
{
	public:
		Bot(const QPolygon &path, Map *map, Scene *scene);

		float x() const override;
		float y() const override;

		void tick(const long delta) override;

		void addPlayerTracking(Player *player);

	private:
		Map *m_map;

		QVector<QLineF> m_path;
		int m_currentLine;
		qreal m_positionInLine;

		bool m_movingForward;

		VisionConeDrawable m_visionCone;
		QVector<Player*> m_trackedPlayers;

//		QSoundEffect m_alarmSound;
};

#endif // BOT_H
