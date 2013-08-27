#include <QPainter>

#include "Scene.h"
#include "IDrawable.h"
#include "Map.h"

Scene::Scene(QQuickWindow *window)
	: m_window(window)
	, m_dirty(false)
{

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
	QRect rect = painter->window();
	QSize size = rect.size();
	QImage image(size, QImage::Format_RGB888);
	QPainter p(&image);

	if(m_dirty)
	{
//		m_drawables.sort(&IDrawable::compare);
		m_dirty = false;
	}

	for(IDrawable *drawable : m_drawables)
	{
//		drawable->draw(&p, cx, cy, delta);

//		QSGTexture *texture = drawable->texture();
//		QPointF position(drawable->x(), drawable->y());
//		position -= m_cameraPosition;
//		QSize size = texture->textureSize();
//		QRectF rect(position, size);

//		QSGSimpleTextureNode *node = (QSGSimpleTextureNode *)drawable;
//		node->setRect(rect);
//		node->setTexture(texture);
	}

	painter->drawImage(0, 0, image);
}
