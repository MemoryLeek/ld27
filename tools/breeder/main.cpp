#include <QCoreApplication>
#include <QImageReader>
#include <QDir>
#include <QDebug>
#include <QDataStream>

#include "MutableSprite.h"
#include "MutableSpriteBundle.h"
#include "QStringEx.h"

MutableSprite process(const QString &filename)
{
	qDebug() << QStringEx::format("Processing file %1", filename);

	MutableSprite sprite;
	QFile file(filename);

	if(file.open(QIODevice::ReadOnly))
	{
		QImageReader reader(&file);
		sprite.setDelay(reader.nextImageDelay());

		for(int i = 0; i < reader.imageCount(); i++)
		{
			QImage frame = reader.read();

			sprite.addFrame(frame);
			reader.jumpToNextImage();
		}
	}
	else
	{
		qDebug() << QStringEx::format("Error opening file '%1' for reading", filename);
	}

	return sprite;
}

int main(int argc, char **argv)
{
	MutableSpriteBundle spriteBundle;
	QCoreApplication application(argc, argv);
	QStringList arguments = application.arguments();
	
	if(arguments.count() > 2)
	{
		QString outputFilename = arguments[1];
		QFile outputFile(outputFilename);

		if(outputFile.open(QIODevice::WriteOnly))
		{
			if(arguments.contains("-R"))
			{
				const QString folder = arguments[3];
				const QDir dir(folder);
				const QStringList fileList = dir.entryList(QDir::Files);

				foreach(const QString &filename, fileList)
				{
					const QString path = QStringEx::format("%1/%2", folder, filename);
					const MutableSprite sprite = process(path);

					if(sprite.isValid())
					{
						spriteBundle.addSprite(sprite);
					}
				}
			}
			else
			{
				const QString filename = arguments[2];
				const MutableSprite sprite = process(filename);

				spriteBundle.addSprite(sprite);
			}

			QDataStream stream(&outputFile);
			stream << spriteBundle;
		}
	}
	
	return 0;
}
