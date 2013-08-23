#ifndef SCENE_H
#define SCENE_H

#include <QSGNode>
#include <QList>

#include "QListEx.h"

class IDrawable;

class Scene : public QSGNode
{
	friend class IDrawable;

	public:
		Scene();

	private:
		void add(IDrawable *drawable);
		void remove(IDrawable *drawable);
		void preprocess() override;

		QListEx<IDrawable> m_drawables;

		bool m_dirty;
};

#endif // SCENE_H
