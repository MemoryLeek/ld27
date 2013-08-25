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
	QPolygonF conePolygon;
	if(!m_bot->isFlipped())
	{
		conePolygon.append(QPointF(conePosition.x(), conePosition.y() + 150));
		conePolygon.append(coneBoundingBox.topRight());
		conePolygon.append(coneBoundingBox.bottomRight());
	}
	else
	{
		conePolygon.append(QPointF(conePosition.x() + 500, conePosition.y() + 150));
		conePolygon.append(coneBoundingBox.topLeft());
		conePolygon.append(coneBoundingBox.bottomLeft());
	}

	QPolygonF intersection = conePolygon.intersected(actorBoundingBox);

	// Return if player is not in cone
	if(intersection.isEmpty())
		return false;

	// Do simple raycasting to 3 points on the character to see if we have true vision
	QVector<QPointF> tracePoints;
	tracePoints << QPointF(actorBoundingBox.center().x(), actorBoundingBox.top())
				<< QPointF(actorBoundingBox.center())
				<< QPointF(actorBoundingBox.center().x(), actorBoundingBox.bottom());

	for(const QPointF &point : tracePoints)
	{
		QLineF ray(conePolygon.at(0), point);
		int rayLength = ray.length();

		bool rayHitWall = false;
		for(int len = 50; len < rayLength; len += 10)
		{
			ray.setLength(len);
			for(const QPolygonF &collidable : m_map->collidables())
			{
				if(collidable.containsPoint(ray.p2(), Qt::OddEvenFill))
				{
					rayHitWall = true;
					break;
				}\
			}
			if(rayHitWall)
				break;
		}

		if(!rayHitWall)
			return true;
	}

	return false;
}
