#ifndef MAP_H
#define MAP_H

#include <QHash>
#include <QImage>

class CollisionMapEntry;

class Map
{
	public:
		enum LayerType
		{
			Background,
			Foreground,
			Collision
		};

		void setBackground(const QImage &background);
		void setForeground(const QImage &foreground);
		void addCollisionMapEntry(CollisionMapEntry *entry);

	private:
		friend QDataStream &operator <<(QDataStream &stream, const Map &map);

		QImage m_foreground;
		QImage m_background;

		QList<QPoint> m_collidables;
		QList<QPolygon> m_paths;
};

#endif // MAP_H
