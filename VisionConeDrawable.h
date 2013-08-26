#ifndef VISIONCONEDRAWABLE_H
#define VISIONCONEDRAWABLE_H

#include "IDrawable.h"

class Bot;
class Map;
class Scene;
class Player;

class VisionConeDrawable : public IDrawable
{
	public:
		VisionConeDrawable(Bot *bot, Map *map, Scene *scene);

		float x() const override;
		float y() const override;

		unsigned int drawingOrder() const override;

		void draw(QPainter *painter, const int cx, const int cy, const int delta) override;

		bool containsActor(const Player &actor);

	private:
		Bot *m_bot;
		Map *m_map;

		QImage m_image;
};

#endif // VISIONCONEDRAWABLE_H
