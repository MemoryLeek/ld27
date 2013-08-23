#ifndef IDRAWABLE_H
#define IDRAWABLE_H

#include <QSGTexture>
#include <QSGSimpleTextureNode>

class Scene;

class IDrawable : private QSGSimpleTextureNode
{
	friend class Scene;

	public:
		IDrawable(Scene *scene);

		virtual ~IDrawable();

		virtual float x() const = 0;
		virtual float y() const = 0;
		virtual unsigned int drawingOrder() const = 0;
		virtual QSGTexture *texture() const = 0;

		static bool compare(IDrawable *d1, IDrawable *d2);

	private:
		Scene *m_scene;
};

#endif // IDRAWABLE_H
