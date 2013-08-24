#include "MapLoader.h"
#include "Map.h"
#include "CollisionMapAnalyzer.h"
#include "CollisionMapAnalyzerResult.h"
#include "CollisionMapEntry.h"

#include <QDir>
#include <QDebug>

MapLoader::MapLoader(Scene *scene)
{
	m_scene = scene;
	m_fileNameLayerMap =
	{
		{ "collision.png", Map::Collision },
		{ "background.png", Map::Background },
		{ "foreground.png", Map::Foreground }
	};
}

Map *MapLoader::load(const QString &folder)
{
	QDir dir(folder);
	QStringList fileList = dir.entryList(QStringList() << "*.png");

	Map *map = new Map(m_scene);

	for(const QString &file : fileList)
	{
		const Map::LayerType &type = m_fileNameLayerMap.value(file);
		const QString &path = dir.filePath(file);
		const QImage image(path);

		switch(type)
		{
			case Map::Background:
			{
				map->setBackground(image);
				break;
			}

			case Map::Foreground:
			{
				map->setForeground(image);
				break;
			}

			case Map::Collision:
			{
				CollisionMapAnalyzer analyzer;
				CollisionMapAnalyzerResult result = analyzer.analyze(image);

				QList<CollisionMapEntry *> entries = result.entries();

				qDebug() << "Number of collidable regions found:" << entries.count();

				for(CollisionMapEntry *entry : entries)
				{
					map->addCollisionMapEntry(entry);
				}

				break;
			}
		}
	}

	return map;
}
