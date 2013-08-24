#include <QFile>
#include <QFile>

#include "MapLoader.h"
#include "Map.h"

MapLoader::MapLoader(Scene *scene)
{
	m_scene = scene;
}

Map *MapLoader::load(const QString &filename)
{
	QFile file(filename);

	if(file.open(QIODevice::ReadOnly))
	{
		Map *map = new Map();

		QDataStream stream(&file);
		stream >> *map;

		return map;
	}

	return 0;
}
