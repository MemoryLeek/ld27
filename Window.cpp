#include <QDir>

#include "Window.h"
#include "QStringEx.h"

Window::Window()
	: m_activeState("LogoState")
{

}

QString Window::activeState() const
{
	return QStringEx::format("States/%1.qml", m_activeState);
}

QStringList Window::availableStates() const
{
	QDir states("States");
	QStringList files = states.entryList(QStringList() << "*.qml");
	QStringList results;

	for(const QString &file : files)
	{
		results << QStringEx::format("States/%1", file);
	}

	return results;
}

void Window::setActiveState(const QString &activeState)
{
	m_activeState = activeState;

	emit activeStateChanged();
}

void Window::initialize()
{
	registerComponent(this);
}
