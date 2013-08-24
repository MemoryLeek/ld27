#ifndef COLLISIONMAPANALYZERRESULT_H
#define COLLISIONMAPANALYZERRESULT_H

#include <QHash>

#include "CollisionMapEntry.h"

class CollisionMapAnalyzerResult
{
	public:
		CollisionMapAnalyzerResult();

		CollisionMapEntry *find(const int x, const int y);
		CollisionMapEntry *createEntry(const int x, const int y);

		QList<CollisionMapEntry *> entries() const;

	private:
		QHash<Coordinate, CollisionMapEntry *> m_index;
		QList<CollisionMapEntry *> m_entries;
};

#endif // COLLISIONMAPANALYZERRESULT_H
