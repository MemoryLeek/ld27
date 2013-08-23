#include <QGuiApplication>
#include <QQmlComponent>
#include <QOpenGLContext>
#include <QDir>

#include "Engine.h"
#include "Window.h"

int main(int argc, char **argv)
{
	QGuiApplication application(argc, argv);

	Engine engine;
	QQmlComponent component(&engine, "Window.qml");
	QObject *object = component.create();

//	QSurfaceFormat format = context.format();
//	format.setSwapBehavior(QSurfaceFormat::SingleBuffer);

	Window *window = (Window *)object;
//	window->setFormat(format);
	window->setWidth(800);
	window->setHeight(600);
	window->initialize();
	window->show();

	return application.exec();
}
