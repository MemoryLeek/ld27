#ifndef BOT_H
#define BOT_H

#include <QSoundEffect>

#include "IDrawable.h"
#include "SpriteBundle.h"

class Player;
class Map;
class VisionConeDrawable;

class Bot : public IDrawable
{
	public:
		Bot(const QPolygon &path, Map *map, Scene *scene);

		float x() const;
		float y() const;

		unsigned int drawingOrder() const override;

		void draw(QPainter *painter, const int cx, const int cy, const int delta) override;

		void addPlayerTracking(Player *player);

		bool isFlipped() const;

	private:
		Map *m_map;

		QVector<QLineF> m_path;
		int m_currentLine;
		qreal m_positionInLine;

		bool m_flipped;
		bool m_movingForward;
//		long m_directionSwitchDelay;

		SpriteBundle m_sprite;
		VisionConeDrawable *m_visionCone;
		QVector<Player*> m_trackedPlayers;

//		QSoundEffect m_alarmSound;
};

#endif // BOT_H
