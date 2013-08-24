#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <QString>
#include <QHash>

#include "Map.h"

class MapLoader
{
	public:
		MapLoader(Scene *scene);

		Map *load(const QString &baseName);

	private:
		Scene *m_scene;
		QHash<QString, Map::LayerType> m_fileNameLayerMap;
};

#endif // MAPLOADER_H
