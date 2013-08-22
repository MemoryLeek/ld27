#ifndef CONTAINER_H
#define CONTAINER_H

#include <QDebug>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlContext>

class Container
{
	public:
		template<class T>
		void registerComponent(T *component)
		{
			QObject *object = (QObject *)this;

			QMetaObject metaObject = T::staticMetaObject;
			QVariant value = QVariant::fromValue<T *>(component);

			QObject *engine = qmlEngine(object) ?: object;
			engine->setProperty(metaObject.className(), value);
		}

		template<class T>
		T *getComponent()
		{
			QObject *object = (QObject *)this;

			QMetaObject metaObject = T::staticMetaObject;
			QObject *engine = qmlEngine(object) ?: object;
			QVariant property = engine->property(metaObject.className());

			return property.value<T *>();
		}
};

#endif // CONTAINER_H
