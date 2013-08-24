#ifndef COLLISIONMAPANALYZER_H
#define COLLISIONMAPANALYZER_H

#include <QImage>
#include <QHash>

class CollisionMapAnalyzerResult;

class CollisionMapAnalyzer
{
	public:
		CollisionMapAnalyzerResult analyze(const QImage &image);
};

#endif // COLLISIONMAPANALYZER_H
