#include "Scene.h"
#include "IDrawable.h"

Scene::Scene(QQuickWindow *window)
	: m_window(window)
	, m_dirty(false)
{
	setFlag(QSGNode::UsePreprocess);
}

QSGTexture *Scene::createTexture(const QImage &image)
{
	return m_window->createTextureFromImage(image);
}

QSGTexture *Scene::createTexture(const QString &filename)
{
	QImage image(filename);
	QSGTexture *texture = createTexture(image);

	return texture;
}

void Scene::add(IDrawable *drawable)
{
	m_drawables << drawable;
	m_dirty = true;

	appendChildNode(drawable);
}

void Scene::remove(IDrawable *drawable)
{
	m_drawables.removeAll(drawable);

	removeChildNode(drawable);
}

void Scene::preprocess()
{
	if(m_dirty)
	{
		m_drawables.sort(&IDrawable::compare);
		m_dirty = false;
	}

	for(IDrawable *drawable : m_drawables)
	{
		QSGTexture *texture = drawable->texture();
		QPoint position(drawable->x(), drawable->y());
		QSize size = texture->textureSize();
		QRect rect(position, size);

		QSGSimpleTextureNode *node = (QSGSimpleTextureNode *)drawable;
		node->setRect(rect);
		node->setTexture(texture);
	}
}
