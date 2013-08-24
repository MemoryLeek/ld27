#include "CollisionMapAnalyzerResult.h"
#include "CollisionMapEntry.h"

CollisionMapEntry *CollisionMapAnalyzerResult::find(const int x, const int y)
{
	const int offset = 5;
	const int size = offset * 2;

	for(int xr = x - offset; xr < x + size; xr++)
	{
		for(int yr = y - offset; yr < y + size; yr++)
		{
			Coordinate query(xr, yr);
			Coordinate coordinate(x, y);
			CollisionMapEntry *entry = m_index.value(query);

			if(entry)
			{
				return m_index
					.insert(coordinate, entry)
					.value();
			}
		}
	}

	return 0;
}

CollisionMapEntry *CollisionMapAnalyzerResult::createEntry(const int x, const int y)
{
	Coordinate coordinate(x, y);
	CollisionMapEntry *entry = new CollisionMapEntry();

	m_entries << entry;
	m_index[coordinate] = entry;

	return entry;
}

QList<CollisionMapEntry *> CollisionMapAnalyzerResult::entries() const
{
	return m_entries;
}
