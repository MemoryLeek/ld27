#ifndef FRAMEIMAGEPROVIDER_H
#define FRAMEIMAGEPROVIDER_H

#include <QQuickImageProvider>

class Compositor;

class FrameImageProvider : public QQuickImageProvider
{
	public:
		FrameImageProvider(Compositor *compositor);

		QImage requestImage(const QString &, QSize *, const QSize &) override;

	private:
		Compositor *m_compositor;
};

#endif // FRAMEIMAGEPROVIDER_H
