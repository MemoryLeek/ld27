#include "Scene.h"
#include "IDrawable.h"

Scene::Scene()
	: m_dirty(false)
{
	setFlag(QSGNode::UsePreprocess);
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

void Scene::preprocess()
{
	if(m_dirty)
	{
		m_drawables.sort(&IDrawable::compare);
		m_dirty = false;
	}

	for(IDrawable *drawable : m_drawables)
	{

	}
}
