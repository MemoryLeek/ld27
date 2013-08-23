#ifndef LOCALIMAGEPROVIDER_H
#define LOCALIMAGEPROVIDER_H

#include <QQuickImageProvider>

class LocalImageProvider : public QQuickImageProvider
{
	public:
		LocalImageProvider();

		QImage requestImage(const QString &id, QSize *, const QSize &);
};

#endif // LOCALIMAGEPROVIDER_H
