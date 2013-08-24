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

		Map();

		void setBackground(const QImage &background);
		void setForeground(const QImage &foreground);
		void addCollisionMapEntry(CollisionMapEntry *entry);

	private:
		QImage m_foreground;
		QImage m_background;
		QList<CollisionMapEntry *> m_entries;
};

#endif // MAP_H
