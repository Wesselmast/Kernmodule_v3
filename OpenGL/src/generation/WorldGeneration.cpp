#include "WorldGeneration.h"

WorldGeneration::WorldGeneration(int size, int height, int amtOfChunks) : size(size), height(height), amtOfChunks(amtOfChunks) {
	chunkGen = new ChunkGenerator(size, height);
}

std::vector<Chunk*> WorldGeneration::generateWorld() {
	int num = std::floor(std::sqrt(amtOfChunks));
	for (int i = -num/2; i < num - (num/2); i++) {
		for (int j = -num/2; j < num - (num/2); j++) {
			chunks.emplace_back(chunkGen->generateChunk(j * size, i * size));
		}
	}
	return chunks;
}

bool WorldGeneration::chunkExists(int x, int z) {
	for (int i = 0; i < chunks.size(); i++) {
		if (chunks[i]->GetXPos() == x && chunks[i]->GetYPos() == z) {
			deleteIndex = i;
			return true;
		}
	}
	return false;
}

void WorldGeneration::deleteChunk() {
	chunks.erase(chunks.begin() + deleteIndex);
	std::cout << "Deleted Chunk" << std::endl;
}

void WorldGeneration::updateChunk(int xPos, int zPos) {
	if (chunkExists(xPos, zPos)) {
		deleteChunk();
	}
	else {
		addChunk(xPos, zPos);
	}
}

void WorldGeneration::addChunk(int x, int z) {
	chunks.emplace_back(chunkGen->generateChunk(x, z));
	std::cout << "Added Chunk" << std::endl;
	incr++;
}

int WorldGeneration::getAmount() {
	return amtOfChunks + incr;
}

WorldGeneration::~WorldGeneration() {
	delete chunkGen;
}