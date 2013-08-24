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
		~MapSurface();

		float x() const override;
		float y() const override;

		unsigned int drawingOrder() const override;

		QSGTexture *texture() override;

	private:
		SurfaceLevel m_surfaceLevel;
		QSGTexture *m_texture;
};

#endif // MAPSURFACE_H
