#ifndef MAP_H
#define MAP_H

#include "IDrawable.h"

#include <QHash>
#include <QImage>

class CollisionMapEntry;
class Scene;

class Map : public IDrawable
{
	public:
		enum LayerType
		{
			Background,
			Foreground,
			Collision
		};

		Map(Scene *scene);

		float x() const;
		float y() const;

		unsigned int drawingOrder() const;

		QSGTexture *texture();

		void setBackground(const QImage &background);
		void setForeground(const QImage &foreground);
		void addCollisionMapEntry(CollisionMapEntry *entry);

	private:
		Scene *m_scene;

		QImage m_foreground;
		QImage m_background;
		QList<QPoint> m_collidables;
		QSGTexture *m_texture;
};

#endif // MAP_H
