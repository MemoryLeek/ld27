#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <QString>
#include <QHash>

#include "Map.h"

class MapLoader
{
	public:
		MapLoader();

		Map load(const QString &baseName);

	private:
		QHash<QString, Map::LayerType> m_fileNameLayerMap;
};

#endif // MAPLOADER_H
