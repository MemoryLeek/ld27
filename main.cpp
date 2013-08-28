#include <QGuiApplication>
#include <QQmlComponent>
#include <QOpenGLContext>
#include <QFontDatabase>
#include <QDir>

#include "Engine.h"
#include "Window.h"

int main(int argc, char **argv)
{
	QGuiApplication application(argc, argv);

	QFontDatabase fontDatabase;
	QDir directory("resources/fonts");
	QStringList filter = { "*.ttf", "*.otf" };
	QStringList availableFonts = directory.entryList(filter);

	foreach(const QString &file, availableFonts)
	{
		const QString &path = directory.filePath(file);
		fontDatabase.addApplicationFont(path);
	}

	Engine engine;

	QUrl url("qrc:/QML/Window.qml");
	QQmlComponent component(&engine, url);
	QObject *object = component.create();

//	QSurfaceFormat format;
//	format.setSwapBehavior(QSurfaceFormat::SingleBuffer);

	Window *window = (Window *)object;
//	window->setFormat(format);
	window->setWidth(800);
	window->setHeight(600);
	window->initialize();
	window->show();

	return application.exec();
}
