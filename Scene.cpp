#include <QPainter>

#include "Scene.h"
#include "IDrawable.h"
#include "Map.h"

Scene::Scene(QQuickWindow *window)
	: m_window(window)
	, m_dirty(false)
{
	setCameraPosition(QPoint(0, 0));
}

void Scene::setCameraPosition(const QPoint &position, Map *map)
{
	QPoint windowCenter(m_window->width() / 2, m_window->height() / 2);
	m_cameraPosition = position - windowCenter;

	if(m_cameraPosition.x() < 0)
		m_cameraPosition.setX(0);
	if(m_cameraPosition.y() < 0)
		m_cameraPosition.setY(0);

	if(!map)
		return;

	if(m_cameraPosition.x() + m_window->width() > map->width())
		m_cameraPosition.setX(map->width() - m_window->width());
	if(m_cameraPosition.y() + m_window->height() > map->height())
		m_cameraPosition.setY(map->height() - m_window->height());
}

void Scene::add(IDrawable *drawable)
{
	m_drawables << drawable;
	m_dirty = true;
}

void Scene::remove(IDrawable *drawable)
{
	m_drawables.removeAll(drawable);
}

void Scene::draw(QPainter *painter, const int cx, const int cy, const int delta)
{
	if(m_dirty)
	{
		m_drawables.sort(&IDrawable::compare);
		m_dirty = false;
	}

	for(IDrawable *drawable : m_drawables)
	{
		drawable->draw(painter, cx, cy, delta);

//		QSGTexture *texture = drawable->texture();
//		QPointF position(drawable->x(), drawable->y());
//		position -= m_cameraPosition;
//		QSize size = texture->textureSize();
//		QRectF rect(position, size);

//		QSGSimpleTextureNode *node = (QSGSimpleTextureNode *)drawable;
//		node->setRect(rect);
//		node->setTexture(texture);
	}
}
