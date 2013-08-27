#ifndef SURFACE_H
#define SURFACE_H

#include <QImage>

#include "ICollectionItem.h"

class Surface : public ICollectionItem<Surface>
{
	public:
		Surface(QSize size, const int order);
		Surface(QImage *image, QPoint position, const int order);

		QImage *image();
		QPoint position() const;

		bool isManaged() const;

		static bool compare(const Surface &s1, const Surface &s2);

	private:
		QImage *m_image;
		QPoint m_position;

		int m_order;
		bool m_managed;
};

#endif // SURFACE_H
