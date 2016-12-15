#include "World.h"
#include <fstream>

World::World() {

}

void World::loadWorld(std::string path, ResourceHolder<sf::Texture, Texture>* res) {
	std::ifstream in(path);
	std::string path_map;

	in >> mNodes;
	mMaps.resize(mNodes);
	mAdj.resize(mNodes);
	for (int i = 0; i < mNodes; ++i) {
		in >> path_map;
		mMaps.insert(mMaps.begin(), new Map(path_map, res));
	}

	int edges, x , y;
	in >> edges;
	for (int i = 0; i < edges; ++i) {
		in >> x >> y;
		mAdj[x].push_front(mMaps[y]);
	}

	in.close();
}