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
	const QPointF botPosition(m_bot->x(), m_bot->y());

	const QRectF actorBoundingBox(actorPosition, actor.texture()->textureSize());
	const QRectF botBoundingBox(botPosition, m_bot->texture()->textureSize());

	const QLineF ray(botBoundingBox.center(), actorBoundingBox.center());
	const QList<Collidable> &collidables = m_map->collidables();

	if(ray.length() < 300)
	{
		if(m_bot->isFlipped())
		{
			if(!(ray.angle() > 165 && ray.angle() < 195))
			{
				return false;
			}
		}
		else
		{
			if(ray.angle() < 345 && ray.angle() > 15)
			{
				return false;
			}
		}

		const float length = ray.length();
		const float step = 1.0f / length;

		for(const Collidable &collidable : collidables)
		{
			const QPolygonF &polygon = collidable.polygon();
			const QRectF &boundingBox = collidable.boundingBox();

			for(float i = 0.0f; i < 1.0f; i += step)
			{
				const QPointF &point = ray.pointAt(i);

				if(boundingBox.contains(point))
				{
					if(polygon.containsPoint(point, Qt::OddEvenFill))
					{
						return false;
					}
				}
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}
