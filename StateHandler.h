#ifndef STATEHANDLER_H
#define STATEHANDLER_H

#include <QObject>
#include <QMetaType>
#include <QRegularExpression>

#include "Container.h"
#include "Window.h"

class StateHandler : public QObject
{
	Q_OBJECT

	public:
		StateHandler(Container *container);

		template<class TState>
		void changeState()
		{
			const QMetaObject &metaObject = TState::staticMetaObject;
			const QString &className = metaObject.className();
			const QString name = QRegularExpression("::(.*)$")
				.match(className)
				.captured(1);

			Window *window = m_container->getComponent<Window>();
			window->setActiveState(name);
		}

	private:
		Container *m_container;
};

Q_DECLARE_METATYPE(StateHandler *)

#endif // STATEHANDLER_H
