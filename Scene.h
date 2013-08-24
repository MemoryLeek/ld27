#ifndef SCENE_H
#define SCENE_H

#include <QSGNode>
#include <QList>
#include <QQuickWindow>

#include "QListEx.h"

class IDrawable;
class Map;

class Scene : public QSGNode
{
	friend class IDrawable;

	public:
		Scene(QQuickWindow *window);

		QSGTexture *createTexture(const QImage &image);
		QSGTexture *createTexture(const QString &filename);

		void setCameraPosition(const QPointF &position, Map *map = NULL);

	private:
		void add(IDrawable *drawable);
		void remove(IDrawable *drawable);
		void preprocess() override;

		QListEx<IDrawable *> m_drawables;
		QQuickWindow *m_window;

		bool m_dirty;

		QPointF m_cameraPosition;
};

#endif // SCENE_H
