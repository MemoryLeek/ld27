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
		VisionConeDrawable(Bot *bot, Map *map);

		float x() const;
		float y() const;

		unsigned int drawingOrder() const;

		void draw(FrameDrawingContext &context, const int cx, const int cy, const int delta) override;

		bool containsActor(const Player &actor);

	private:
		Bot *m_bot;
		Map *m_map;

		QImage m_image;
};

#endif // VISIONCONEDRAWABLE_H
