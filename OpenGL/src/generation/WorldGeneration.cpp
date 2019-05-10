#include "WorldGeneration.h"


WorldGeneration::WorldGeneration(ChunkManager* man, Camera* player) : man(man), player(player) {
}

void WorldGeneration::generateWorld(int size, int height, int amtOfChunks, int amtOfOctaves, float heightScale, int chanceAtBiome) {
	chunkGen = new ChunkGenerator(size, height, amtOfOctaves);
	this->size = size;
	this->amtOfChunks = amtOfChunks;
	this->heightScale = heightScale;
	startBiomeInterval = chanceAtBiome;
	biomeInterval = startBiomeInterval;

	pickNextBiome();
	man->addChunk(*(chunkGen->generateChunk(0, 0, heightScale, type)));
}

void WorldGeneration::updateChunks() {
	std::vector<glm::vec2> temp = getNeighbours();
	if (temp.size() != 0) {
		if (biomeInterval <= 0) {
			pickNextBiome();
			biomeInterval = startBiomeInterval;
		}
		else biomeInterval -= 1;
	}
	for (int i = 0; i < temp.size(); i++) {
		man->addChunk(*(chunkGen->generateChunk(temp[i].x, temp[i].y, heightScale, type)));
	}
}

std::vector<glm::vec2> WorldGeneration::getNeighbours() const {
	std::vector<glm::vec2> temp;
	const glm::vec2 thisChunk = glm::vec2(man->getChunk(player->getXPos(), player->getZPos())->getXPos(), man->getChunk(player->getXPos(), player->getZPos())->getZPos());

	//spawn chunks around the origin that don't exist yet
	const int num = std::floor(std::sqrt(amtOfChunks));
	for (int i = -num / 2; i < num - (num / 2); i++) {
		for (int j = -num / 2; j < num - (num / 2); j++) {
			if (i == 0 && j == 0) continue;
			if (!man->chunkExist(i * size + thisChunk.x, j * size + thisChunk.y)) {
				temp.push_back(glm::vec2(i * size + thisChunk.x, j * size + thisChunk.y));
			}
		}
	}
	return temp;
}

void WorldGeneration::pickNextBiome() {
	if (rand() % biomePool == 0) type = Desert;
	if (rand() % biomePool == 1) type = Forest;
}

WorldGeneration::~WorldGeneration() {
	delete chunkGen;
}