#ifndef BOT_H
#define BOT_H

#include "Actor.h"

class Bot : public Actor
{
	public:
		Bot(const QPolygon &path, Scene *scene);

		float x() const override;
		float y() const override;

		void tick(const long delta) override;

	private:
		void reloadPath(bool reverse = false);

		const QPolygon m_path;
		QVector<QLineF> m_workPath;

		bool m_movingForward;
};

#endif // BOT_H
