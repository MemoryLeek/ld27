#ifndef COLLISIONMAPANALYZER_H
#define COLLISIONMAPANALYZER_H

#include <QImage>
#include <QHash>

class CollisionMapAnalyzerResult;

class CollisionMapAnalyzer
{
	public:
		CollisionMapAnalyzer();

		CollisionMapAnalyzerResult analyze(const QImage &image);

	private:
		enum PixelType
		{
			Collision = 1,
			Path
		};
};

#endif // COLLISIONMAPANALYZER_H
