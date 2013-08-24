//#include <QRectF>

#include "Bot.h"
#include "Scene.h"

#include "VisionConeDrawable.h"

VisionConeDrawable::VisionConeDrawable(Bot *bot, Scene *scene)
	: IDrawable(scene),
	  m_bot(bot)
{
	QImage image("resources/viewcone.png");
	m_texture = scene->createTexture(image);
	m_textureFlipped = scene->createTexture(image.mirrored(true, false));
}

float VisionConeDrawable::x() const
{
	return (m_bot->isFlipped()) ? m_bot->x() - 500 + 16 : m_bot->x() + 16;
}

float VisionConeDrawable::y() const
{
	return m_bot->y() - 135;
}

unsigned int VisionConeDrawable::drawingOrder() const
{
	return m_bot->drawingOrder() + 1;
}

QSGTexture *VisionConeDrawable::texture()
{
	return (m_bot->isFlipped()) ? m_textureFlipped : m_texture;
}

bool VisionConeDrawable::containsActor(Actor &actor)
{
	// Do rough bounding box check first
	QPointF actorPosition(actor.x(), actor.y());
	QRectF actorBoundingBox(actorPosition, actor.texture()->textureSize());

	QPointF conePosition(x(), y());
	QRectF coneBoundingBox(conePosition, texture()->textureSize());

	if(!coneBoundingBox.intersects(actorBoundingBox))
		return false;

	// Finer check if the Actor is inside the bounding box
	QPolygonF poly;
	if(!m_bot->isFlipped())
	{
		poly.append(QPointF(conePosition.x(), conePosition.y() + 150));
		poly.append(coneBoundingBox.topRight());
		poly.append(coneBoundingBox.bottomRight());
	}
	else
	{
		poly.append(QPointF(conePosition.x() + 500, conePosition.y() + 150));
		poly.append(coneBoundingBox.topLeft());
		poly.append(coneBoundingBox.bottomLeft());
	}
	return !poly.intersected(actorBoundingBox).isEmpty();
}
