#ifndef SCENE_H
#define SCENE_H

#include <QSGNode>
#include <QList>
#include <QQuickWindow>

#include "QListEx.h"

class IDrawable;
class Map;

class Scene
{
	friend class IDrawable;

	public:
		Scene(QQuickWindow *window);

		void setCameraPosition(const QPoint &position, Map *map = 0);
		void draw(QPainter *painter, const int cx, const int cy, const int delta);

	private:
		void add(IDrawable *drawable);
		void remove(IDrawable *drawable);

		QListEx<IDrawable *> m_drawables;
		QQuickWindow *m_window;

		bool m_dirty;

		QPoint m_cameraPosition;
};

#endif // SCENE_H
