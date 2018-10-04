#include "WorldGeneration.h"


WorldGeneration::WorldGeneration(int size, int height, int amtOfChunks) : size(size), height(height), amtOfChunks(amtOfChunks) {
	chunkGen = new ChunkGenerator(size, height);
}

//make all the chunks in a grid pattern and add them to a list, making sure 0,0 is in the middle of the grid
std::vector<Chunk*> WorldGeneration::generateWorld() {
	int num = std::floor(std::sqrt(amtOfChunks));
	for (int i = -num/2; i < num - (num/2); i++) {
		for (int j = -num/2; j < num - (num/2); j++) {
			chunks.emplace_back(chunkGen->generateChunk(j * size, i * size));
		}
	}
	return chunks;
}

WorldGeneration::~WorldGeneration() {
	delete chunkGen;
}