#include <QFile>
#include <QDataStream>

#include "SpriteLoader.h"
#include "SpriteBundle.h"

SpriteBundle SpriteLoader::load(const QString &filename)
{
	QFile file(filename);
	SpriteBundle bundle;

	if(file.open(QIODevice::ReadOnly))
	{
		QDataStream stream(&file);
		stream >> bundle;
	}

	return bundle;
}
