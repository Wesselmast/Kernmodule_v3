#include "WorldGeneration.h"

WorldGeneration::WorldGeneration(int size, int height, int amtOfChunks) : size(size), height(height), amtOfChunks(amtOfChunks) {
	chunkGen = new ChunkGenerator(size, height);
}

std::vector<Chunk*> WorldGeneration::generateWorld() {
	for (int i = 0; i < std::sqrt(amtOfChunks); i++) {
		for (int j = 0; j < std::sqrt(amtOfChunks); j++) {
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