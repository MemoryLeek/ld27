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
		void reloadPath(bool reverse = false);

		const QPolygon m_path;
		QVector<QLineF> m_workPath;

		bool m_movingForward;

		VisionConeDrawable m_visionCone;
		QVector<Player*> m_trackedPlayers;
};

#endif // BOT_H
