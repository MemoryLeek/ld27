#ifndef STATE_H
#define STATE_H

#include <QRegularExpression>

#include "Window.h"
#include "Container.h"
#include "VisualObject.h"

template<class T>
class State
	: public VisualObject<T>
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
