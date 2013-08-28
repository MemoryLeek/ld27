#ifndef COMPOSITOR_H
#define COMPOSITOR_H

#include <QPainter>
#include <QMetaType>

#include "FrameDrawingContext.h"

class Compositor : public QObject
{
	Q_OBJECT

	public:
		QImage lastFrame() const;

		void composite(FrameDrawingContext *context, QPainter *painter);

	private:
		QSharedPointer<FrameDrawingContext> m_lastFrame;
};

Q_DECLARE_METATYPE(Compositor *)

#endif // COMPOSITOR_H
