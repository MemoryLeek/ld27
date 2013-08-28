#include <QDebug>

#include "DeferredPaintEngine.h"
#include "RenderingCommand.h"

DeferredPaintEngine::~DeferredPaintEngine()
{
	for(IRenderingCommand *command : m_commands)
	{
		command->deleteLater();
	}
}

void DeferredPaintEngine::draw(QPainter *painter) const
{
	for(IRenderingCommand *command : m_commands)
	{
		command->invoke(painter);
	}
}
bool DeferredPaintEngine::begin(QPaintDevice *)
{
	return true;
}

bool DeferredPaintEngine::end()
{
	return true;
}

void DeferredPaintEngine::drawEllipse(const QRectF &r)
{
	m_commands << new RenderingCommand<const QRectF &>(&QPainter::drawEllipse, r);
}

void DeferredPaintEngine::drawEllipse(const QRect &r)
{
	m_commands << new RenderingCommand<const QRect &>(&QPainter::drawEllipse, r);
}

void DeferredPaintEngine::drawImage(const QRectF &r, const QImage &pm, const QRectF &sr, Qt::ImageConversionFlags flags)
{
	m_commands << new RenderingCommand<const QRectF &, const QImage &, const QRectF &, Qt::ImageConversionFlags>(&QPainter::drawImage, r, pm, sr, flags);
}

void DeferredPaintEngine::drawLines(const QLineF *lines, int lineCount)
{
	m_commands << new RenderingCommand<const QLineF *, int>(&QPainter::drawLines, lines, lineCount);
}

void DeferredPaintEngine::drawLines(const QLine *lines, int lineCount)
{
	m_commands << new RenderingCommand<const QLine *, int>(&QPainter::drawLines, lines, lineCount);
}

void DeferredPaintEngine::drawPath(const QPainterPath &path)
{
	m_commands << new RenderingCommand<const QPainterPath &>(&QPainter::drawPath, path);
}

void DeferredPaintEngine::drawPixmap(const QRectF &r, const QPixmap &pm, const QRectF &sr)
{
	m_commands << new RenderingCommand<const QRectF &, const QPixmap &, const QRectF &>(&QPainter::drawPixmap, r, pm, sr);
}

void DeferredPaintEngine::drawPoints(const QPointF *points, int pointCount)
{
	m_commands << new RenderingCommand<const QPointF *, int>(&QPainter::drawPoints, points, pointCount);
}

void DeferredPaintEngine::drawPoints(const QPoint *points, int pointCount)
{
	m_commands << new RenderingCommand<const QPoint *, int>(&QPainter::drawPoints, points, pointCount);
}

void DeferredPaintEngine::drawPolygon(const QPointF *, int, QPaintEngine::PolygonDrawMode)
{

}

void DeferredPaintEngine::drawPolygon(const QPoint *, int, QPaintEngine::PolygonDrawMode)
{

}

void DeferredPaintEngine::drawRects(const QRectF *rects, int rectCount)
{
	m_commands << new RenderingCommand<const QRectF *, int>(&QPainter::drawRects, rects, rectCount);
}

void DeferredPaintEngine::drawRects(const QRect *rects, int rectCount)
{
	m_commands << new RenderingCommand<const QRect *, int>(&QPainter::drawRects, rects, rectCount);
}

void DeferredPaintEngine::drawTextItem(const QPointF &p, const QTextItem &textItem)
{
	m_commands << new RenderingCommand<const QPointF &, const QTextItem &>(&QPainter::drawTextItem, p, textItem);
}

void DeferredPaintEngine::drawTiledPixmap(const QRectF &r, const QPixmap &pixmap, const QPointF &s)
{
	m_commands << new RenderingCommand<const QRectF &, const QPixmap &, const QPointF &>(&QPainter::drawTiledPixmap, r, pixmap, s);
}

void DeferredPaintEngine::updateState(const QPaintEngineState &)
{

}

QPaintEngine::Type DeferredPaintEngine::type() const
{
	return QPaintEngine::User;
}
