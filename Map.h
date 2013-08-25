#ifndef MAP_H
#define MAP_H

#include "IDrawable.h"
#include "Collidable.h"

#include <QHash>
#include <QImage>

class Scene;
class MapSurface;

class Map
{
	public:
		void initialize(Scene *scene);

		int width() const;
		int height() const;

		QList<Collidable> collidables() const;
		QList<QPolygon> paths() const;

		QPoint spawnPoint() const;
		QRect goal() const;

	private:
		friend QDataStream &operator >>(QDataStream &stream, Map &map);

		MapSurface *m_backgroundSurface;
		MapSurface *m_foregroundSurface;

		QImage m_foreground;
		QImage m_background;

		QList<Collidable> m_collidables;
		QList<QPolygon> m_paths;

		QPoint m_spawn;
		QRect m_goal;
};

#endif // MAP_H
