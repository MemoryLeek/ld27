#include <QPainter>

#include "Map.h"
#include "CollisionMapEntry.h"
#include "Scene.h"

Map::Map(Scene *scene)
	: IDrawable(scene)
{
	m_scene = scene;
}

float Map::x() const
{
	return 0;
}

float Map::y() const
{
	return 0;
}

unsigned int Map::drawingOrder() const
{
	return 0;
}

QSGTexture *Map::texture()
{
	if(!m_texture)
	{
		QSize size = m_background.size();
		QImage image(size, QImage::Format_ARGB32);
		QPainter painter(&image);

		for(const QPoint &point : m_collidables)
		{
			painter.setBrush(Qt::red);
			painter.setPen(Qt::red);
			painter.drawPoint(point);
		}

		m_texture = m_scene->createTexture(image);
	}

	return m_texture;
}

void Map::setBackground(const QImage &background)
{
	m_background = background;
}

void Map::setForeground(const QImage &foreground)
{
	m_foreground = foreground;
}

void Map::addCollisionMapEntry(CollisionMapEntry *entry)
{
	m_collidables << entry->compile();
}
