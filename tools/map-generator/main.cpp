#include <QCoreApplication>
#include <QStringList>
#include <QDataStream>
#include <QFile>
#include <QDebug>

#include "MapLoader.h"
#include "Map.h"
#include "QStringEx.h"

int main(int argc, char **argv)
{
	QCoreApplication application(argc, argv);
	QStringList arguments = application.arguments();

	if(arguments.count() > 1)
	{
		QString baseName = arguments[1];
		QString outputFilename = QStringEx::format("%1.map", baseName);
		QFile outputFile(outputFilename);

		if(outputFile.open(QIODevice::WriteOnly))
		{
			MapLoader mapLoader;
			Map map = mapLoader.load(baseName);

			QDataStream stream(&outputFile);
			stream << map;
		}
		else
		{
			qDebug() << "Could not open output file for writing";
		}
	}

	return 0;
}
