#include "WorldGeneration.h"


WorldGeneration::WorldGeneration(ChunkManager* man, Camera* player) : man(man), player(player) {
}

//make all the chunks in a grid pattern and add them to a list, making sure 0,0 is in the middle of the grid
std::vector<Chunk*> WorldGeneration::generateWorld(int size, int height, int amtOfChunks, int amtOfOctaves) {
	this->size = size;
	this->height = height;
	this->amtOfChunks = amtOfChunks;
	this->amtOfOctaves = amtOfOctaves;

	chunkGen = new ChunkGenerator(size, height, amtOfOctaves);
	num = std::floor(std::sqrt(amtOfChunks));

	for (int i = -num/2; i < num - (num/2); i++) {
		for (int j = -num/2; j < num - (num/2); j++) {
			chunks.emplace_back(chunkGen->generateChunk(j * size, i * size));
		}
	}
	return chunks;
}

void WorldGeneration::updateChunks() {
	std::vector <glm:: vec2> temp = getNeighbours();
	for (int i = 0; i < temp.size(); i++) {
		man->AddChunk(*(chunkGen->generateChunk(temp[i].x, temp[i].y)));
	}
}

std::vector<glm::vec2> WorldGeneration::getNeighbours() {
	std::vector<glm::vec2> temp;
	glm::vec2 thisChunk = glm::vec2(man->GetChunk(player->getXPos(), player->getZPos())->GetXPos(), man->GetChunk(player->getXPos(), player->getZPos())->GetYPos());

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
WorldGeneration::~WorldGeneration() {
	delete chunkGen;
}