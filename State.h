#ifndef STATE_H
#define STATE_H

#include <QQuickItem>
#include <QRegularExpression>

#include "Window.h"
#include "Container.h"
#include "VisualObject.h"

class State
	: public QQuickItem
	, public Container
{
	protected:
		template<class TState>
		void changeState()
		{
			const QMetaObject &metaObject = TState::staticMetaObject;
			const QString &className = metaObject.className();
			const QString name = QRegularExpression("::(.*)$")
				.match(className)
				.captured(1);

			Window *window = getComponent<Window>();
			window->setActiveState(name);
		}
};

#endif // STATE_H
