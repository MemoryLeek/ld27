#ifndef DEFERREDPAINTENGINE_H
#define DEFERREDPAINTENGINE_H

#include <QPaintEngine>
#include <QAtomicInt>
#include <QList>

class IRenderingCommand;

class DeferredPaintEngine : public QPaintEngine
{
	public:
		~DeferredPaintEngine();

		void draw(QPainter *painter) const;

		bool begin(QPaintDevice *) override;
		bool end() override;

		void drawEllipse(const QRectF &r) override;
		void drawEllipse(const QRect &r) override;
		void drawImage(const QRectF &r, const QImage &pm, const QRectF &sr, Qt::ImageConversionFlags flags) override;
		void drawLines(const QLineF *lines, int lineCount) override;
		void drawLines(const QLine *lines, int lineCount) override;
		void drawPath(const QPainterPath &path) override;
		void drawPixmap(const QRectF &r, const QPixmap &pm, const QRectF &sr) override;
		void drawPoints(const QPointF *points, int pointCount) override;
		void drawPoints(const QPoint *points, int pointCount) override;
		void drawPolygon(const QPointF *, int, PolygonDrawMode) override;
		void drawPolygon(const QPoint *, int, PolygonDrawMode) override;
		void drawRects(const QRectF *rects, int rectCount) override;
		void drawRects(const QRect *rects, int rectCount) override;
		void drawTextItem(const QPointF &p, const QTextItem &textItem) override;
		void drawTiledPixmap(const QRectF &r, const QPixmap &pixmap, const QPointF &s) override;
		void updateState(const QPaintEngineState &) override;

		Type type() const override;

	private:
		QList<IRenderingCommand *> m_commands;
};

#endif // DEFERREDPAINTENGINE_H
