#include "WorldGeneration.h"


WorldGeneration::WorldGeneration(ChunkManager* man, Camera* player) : man(man), player(player) {
}

void WorldGeneration::generateWorld(int size, int height, int amtOfChunks, int amtOfOctaves, float heightScale) {
	chunkGen = new ChunkGenerator(size, height, amtOfOctaves);
	this->size = size;
	this->amtOfChunks = amtOfChunks;
	this->heightScale = heightScale;

	if (rand() % 2 == 1) type = Desert;
	else type = Forest;

	//start off with one chunk at origin
	man->AddChunk(*(chunkGen->generateChunk(0, 0, heightScale, type)));
}

void WorldGeneration::updateChunks(int chanceAtBiome) {
	std::vector <glm:: vec2> temp = getNeighbours();
	if (rand() % chanceAtBiome == 1) {
		type = changeBiome();
	}
	for (int i = 0; i < temp.size(); i++) {
		man->AddChunk(*(chunkGen->generateChunk(temp[i].x, temp[i].y, heightScale, type)));
	}
}

std::vector<glm::vec2> WorldGeneration::getNeighbours() {
	std::vector<glm::vec2> temp;
	glm::vec2 thisChunk = glm::vec2(man->GetChunk(player->getXPos(), player->getZPos())->GetXPos(), man->GetChunk(player->getXPos(), player->getZPos())->GetYPos());

	//spawn chunks around the origin that don't exist yet
	int num = std::floor(std::sqrt(amtOfChunks));
	for (int i = -num / 2; i < num - (num / 2); i++) {
		for (int j = -num / 2; j < num - (num / 2); j++) {
			if (i == 0 && j == 0) {
				continue;
			}
			if (!man->ChunkExist(i * size + thisChunk.x, j * size + thisChunk.y)) {
				temp.push_back(glm::vec2(i * size + thisChunk.x, j * size + thisChunk.y));
			}
		}
	}
	return temp;
}

biome WorldGeneration::changeBiome() {
	int randomBiome = rand() % 2;
	if (randomBiome == 0)  return Desert;
	if (randomBiome == 1)  return Forest;
}

WorldGeneration::~WorldGeneration() {
	delete chunkGen;
}