#include "WorldGeneration.h"

WorldGeneration::WorldGeneration(int size, int height, int amtOfChunks) : size(size), height(height), amtOfChunks(amtOfChunks) {
	chunkGen = new ChunkGenerator(size, height);
}

std::vector<Chunk*> WorldGeneration::generateWorld() {
	int num = std::sqrt(amtOfChunks);
	for (int i = -num/2; i < num/2; i++) {
		for (int j = -num/2; j < num/2; j++) {
			chunks.emplace_back(chunkGen->generateChunk(j * size, i * size));
		}
	}
	return chunks;
}

int WorldGeneration::getAmount() {
	return amtOfChunks;
}

WorldGeneration::~WorldGeneration() {
	delete chunkGen;
}