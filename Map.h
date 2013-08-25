#ifndef MAP_H
#define MAP_H

#include "IDrawable.h"

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

		bool isCollidable(const int x, const int y);

		QList<QPolygon> paths() const;

	private:
		friend QDataStream &operator >>(QDataStream &stream, Map &map);

		MapSurface *m_backgroundSurface;
		MapSurface *m_foregroundSurface;

		QImage m_foreground;
		QImage m_background;

		QList<QPolygon> m_collidables;
		QList<QPolygon> m_paths;
};

#endif // MAP_H
