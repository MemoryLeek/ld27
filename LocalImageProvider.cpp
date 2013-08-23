#include "LocalImageProvider.h"

LocalImageProvider::LocalImageProvider()
	: QQuickImageProvider(QQuickImageProvider::Image)
{

}

QImage LocalImageProvider::requestImage(const QString &id, QSize *, const QSize &)
{
	return QImage(id);
}
