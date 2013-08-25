#include "Bot.h"
#include "Map.h"
#include "Scene.h"

#include "VisionConeDrawable.h"

VisionConeDrawable::VisionConeDrawable(Bot *bot, Map *map, Scene *scene)
	: IDrawable(scene),
	  m_bot(bot),
	  m_map(map)
{
	QImage image("resources/viewcone.png");
	m_texture = scene->createTexture(image);
	m_textureFlipped = scene->createTexture(image.mirrored(true, false));
}

float VisionConeDrawable::x() const
{
	return (m_bot->isFlipped()) ? m_bot->x() - 300 + 16 : m_bot->x() + 16;
}

float VisionConeDrawable::y() const
{
	return m_bot->y() - 62;
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
	const QPointF actorPosition(actor.x(), actor.y());
	const QRectF actorBoundingBox(actorPosition, actor.texture()->textureSize());

	QLineF ray(QPointF(x(), y() + 77), actorBoundingBox.center());
	if(m_bot->isFlipped())
	{
		ray.setP1(QPointF(x() + 300, y() + 77));
		if(!(ray.angle() > 165 && ray.angle() < 195))
			return false;
	}
	else
	{
		if(ray.angle() < 345 && ray.angle() > 15)
			return false;
	}

	if(ray.length() > 300)
		return false;

	int rayLength = ray.length();
	bool rayHitWall = false;
	for(int len = 10; len < rayLength; len += 2)
	{
		ray.setLength(len);

		for(const Collidable &collidable : m_map->collidables())
		{
			if(!collidable.boundingBox().contains(ray.p2().x(), ray.p2().y()))
				continue;

			const QPolygonF &polygon = collidable.polygon();

			if(polygon.containsPoint(ray.p2(), Qt::OddEvenFill))
			{
				rayHitWall = true;
				break;
			}\
		}

		if(rayHitWall)
			break;
	}

	return !rayHitWall;
}
