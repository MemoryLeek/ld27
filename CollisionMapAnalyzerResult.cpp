#include "CollisionMapAnalyzerResult.h"
#include "CollisionMapEntry.h"

CollisionMapAnalyzerResult::CollisionMapAnalyzerResult()
{

}

CollisionMapEntry *CollisionMapAnalyzerResult::find(const int x, const int y)
{
	for(int xr = x - OFFSET; xr < x + OFFSET; xr++)
	{
		for(int yr = y - OFFSET; yr < y + OFFSET; yr++)
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
