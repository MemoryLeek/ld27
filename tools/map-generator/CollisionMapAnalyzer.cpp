#include <QDebug>

#include "CollisionMapAnalyzer.h"
#include "CollisionMapAnalyzerResult.h"
#include "CollisionMapEntry.h"

CollisionMapAnalyzerResult CollisionMapAnalyzer::analyze(const QImage &image)
{
	CollisionMapAnalyzerResult result;

	const int width = image.width();
	const int height = image.height();

	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			const unsigned int pixel = image.pixel(x, y);

			switch(pixel)
			{
				case CollisionMapEntry::Collision:
				{
					CollisionMapEntry *entry = result.find(x, y, CollisionMapEntry::Collision);
					entry->addPoint(x, y);

					break;
				}

				case CollisionMapEntry::Path:
				{
					CollisionMapEntry *entry = result.find(x, y, CollisionMapEntry::Path);
					entry->addPoint(x, y);

					break;
				}

				case CollisionMapEntry::Spawn:
				{
					CollisionMapEntry *entry = result.createEntry(x, y, CollisionMapEntry::Spawn);
					entry->addPoint(x, y);

					break;
				}

				case CollisionMapEntry::Goal:
				{
					CollisionMapEntry *entry = result.find(x, y, CollisionMapEntry::Goal);
					entry->addPoint(x, y);

					break;
				}

				default:
				{
					break;
				}
			}
		}
	}

	return result;
}
