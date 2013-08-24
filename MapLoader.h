#ifndef MAPLOADER_H
#define MAPLOADER_H

class Map;
class Scene;

class MapLoader
{
	public:
		MapLoader(Scene *scene);

		Map *load(const QString &filename);

	private:
		Scene *m_scene;
};

#endif // MAPLOADER_H
