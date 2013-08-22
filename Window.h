#ifndef WINDOW_H
#define WINDOW_H

#include <QQuickWindow>

#include "Container.h"

class Window
	: public QQuickWindow
	, public Container
{
	Q_OBJECT

	Q_PROPERTY(QString activeState READ activeState NOTIFY activeStateChanged)
	Q_PROPERTY(QStringList availableStates READ availableStates NOTIFY availableStatesChanged)

	public:
		Window();

		QString activeState() const;
		QStringList availableStates() const;

		void setActiveState(const QString &activeState);
		void initialize();

	private:
		QString m_activeState;
		QStringList m_availableStates;

	signals:
		void activeStateChanged();
		void availableStatesChanged();
};

Q_DECLARE_METATYPE(Window *)

#endif // WINDOW_H
