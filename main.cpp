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

	QUrl url("qrc:/QML/Window.qml");
	QQmlComponent component(&engine, url);
	QObject *object = component.create();

	QSurfaceFormat format;
	format.setSwapBehavior(QSurfaceFormat::SingleBuffer);

	Window *window = (Window *)object;
	window->setFormat(format);
	window->setWidth(800);
	window->setHeight(600);
	window->initialize();
	window->show();

	return application.exec();
}
