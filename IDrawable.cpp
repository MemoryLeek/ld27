#include "IDrawable.h"
#include "Scene.h"

IDrawable::IDrawable(Scene *scene)
{
	m_scene = scene;
	m_scene->add(this);
}

IDrawable::~IDrawable()
{
	m_scene->remove(this);
}

bool IDrawable::compare(IDrawable *d1, IDrawable *d2)
{
	return d1->drawingOrder() < d2->drawingOrder();
}
