#include <QGuiApplication>
#include <QQmlComponent>

#include "Engine.h"
#include "Window.h"

int main(int argc, char **argv)
{
	QGuiApplication application(argc, argv);

	Engine engine;
	QQmlComponent component(&engine, "Window.qml");
	QObject *object = component.create();

	Window *window = (Window *)object;
	window->setWidth(800);
	window->setHeight(600);
	window->show();

	return application.exec();
}
