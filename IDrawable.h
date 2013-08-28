#ifndef IDRAWABLE_H
#define IDRAWABLE_H

#include <QSGTexture>
#include <QSGSimpleTextureNode>

class Scene;
class FrameDrawingContext;

class IDrawable
{
	public:
		virtual void draw(FrameDrawingContext *context, const int cx, const int cy, const int delta) = 0;
};

#endif // IDRAWABLE_H
