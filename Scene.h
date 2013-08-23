#ifndef SCENE_H
#define SCENE_H

#include <QSGNode>
#include <QList>
#include <QQuickWindow>

#include "QListEx.h"
#include "DrawableContainer.h"

class IDrawable;

class Scene : public QSGNode
{
	friend class IDrawable;

	public:
		Scene(QQuickWindow *window);

		QSGTexture *createTexture(const QImage &image);
		QSGTexture *createTexture(const QString &filename);

	private:
		void add(IDrawable *drawable);
		void remove(IDrawable *drawable);
		void preprocess() override;

		QListEx<IDrawable *> m_drawables;
		QQuickWindow *m_window;

		bool m_dirty;
};

#endif // SCENE_H
