#ifndef MAPSURFACE_H
#define MAPSURFACE_H

#include <QSGTexture>

#include "IDrawable.h"

class MapSurface : public IDrawable
{
	public:
		enum SurfaceLevel
		{
			Background = 0,
			Foreground = 3
		};

		MapSurface(const SurfaceLevel surfaceLevel, const QImage &image, Scene *scene);

		float x() const override;
		float y() const override;

		unsigned int drawingOrder() const override;

		void draw(QPainter *painter, const int cx, const int cy, const int delta) override;

	private:
		SurfaceLevel m_surfaceLevel;
		QImage m_image;
};

#endif // MAPSURFACE_H
