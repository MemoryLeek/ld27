#ifndef MAP_H
#define MAP_H

#include "IDrawable.h"

#include <QHash>
#include <QImage>

class Scene;

class Map : public IDrawable
{
	public:
		Map(Scene *scene);

		float x() const;
		float y() const;

		unsigned int drawingOrder() const;

		QSGTexture *texture();

	private:
		friend QDataStream &operator >>(QDataStream &stream, Map &map);

		Scene *m_scene;

		QImage m_foreground;
		QImage m_background;
		QList<QPoint> m_collidables;
		QSGTexture *m_texture;
};

#endif // MAP_H
