#include <QPainter>

#include "VisionConeDrawable.h"
#include "FrameDrawingContext.h"
#include "Player.h"
#include "Bot.h"
#include "Map.h"
#include "Scene.h"

VisionConeDrawable::VisionConeDrawable(Bot *bot, Map *map, Scene *scene)
{
	m_bot = bot;
	m_map = map;
	m_image = QImage("resources/viewcone.png");
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

void VisionConeDrawable::draw(FrameDrawingContext &context, const int cx, const int cy, const int delta)
{
	const QImage &m = m_image.mirrored(m_bot->isFlipped(), false);
	const QPoint cameraPosition(cx, cy);
	const QPoint position(x(), y());
	const QPoint adjusted = position - cameraPosition;

	QImage &surface = context.background();
	QPainter painter(&surface);

	painter.drawImage(adjusted, m);
}

bool VisionConeDrawable::containsActor(const Player &actor)
{
	const QPointF actorPosition(actor.x(), actor.y());
	const QPointF botPosition(m_bot->x(), m_bot->y());

	const QSize playerSize(32, 64);
	const QSize botSize(32, 64);

	const QRectF actorBoundingBox(actorPosition, playerSize);
	const QRectF botBoundingBox(botPosition, botSize);

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
