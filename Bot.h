#ifndef BOT_H
#define BOT_H

#include "VisionConeDrawable.h"

#include "Actor.h"

class Player;

class Bot : public Actor
{
	public:
		Bot(const QPolygon &path, Scene *scene);

		float x() const override;
		float y() const override;

		void tick(const long delta) override;

		void addPlayerTracking(Player *player);

	private:
		QVector<QLineF> m_path;
		uint m_currentLine;
		qreal m_positionInLine;

		bool m_movingForward;

		VisionConeDrawable m_visionCone;
		QVector<Player*> m_trackedPlayers;
};

#endif // BOT_H
