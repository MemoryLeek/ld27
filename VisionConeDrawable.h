#ifndef VISIONCONEDRAWABLE_H
#define VISIONCONEDRAWABLE_H

#include "Actor.h"

#include "IDrawable.h"

class Bot;
class Scene;

class VisionConeDrawable : public IDrawable
{
	public:
		VisionConeDrawable(Bot *bot, Scene *scene);

		float x() const override;
		float y() const override;
		unsigned int drawingOrder() const override;
		QSGTexture *texture() override;

		bool containsActor(Actor &actor);

	private:
		Bot *m_bot;

		QSGTexture *m_texture;
		QSGTexture *m_textureFlipped;
};

#endif // VISIONCONEDRAWABLE_H
