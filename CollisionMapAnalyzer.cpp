#include "CollisionMapAnalyzer.h"
#include "CollisionMapAnalyzerResult.h"
#include "CollisionMapEntry.h"

CollisionMapAnalyzer::CollisionMapAnalyzer()
{

}

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
			const unsigned int foo = qAlpha(pixel) / 255;

			switch(foo)
			{
				case Collision:
				{
					CollisionMapEntry *entry = result.find(x, y) ?: result.createEntry(x, y);
					entry->addPoint(x, y);

					break;
				}

				case Path:
				{
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
