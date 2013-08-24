#include <QPainter>

#include "Map.h"
#include "Scene.h"

Map::Map(Scene *scene)
	: IDrawable(scene)
{
	m_scene = scene;
	m_texture = 0;
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

		painter.drawImage(0, 0, m_background);

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

QDataStream &operator >>(QDataStream &stream, Map &map)
{
	stream >> map.m_background;
	stream >> map.m_foreground;
	stream >> map.m_collidables;

	return stream;
}
