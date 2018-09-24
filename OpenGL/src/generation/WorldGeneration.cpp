#include "WorldGeneration.h"

WorldGeneration::WorldGeneration(int size, int height)
{
	ChunkGenerator c(size,height);

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			c.setChunkOffset(i * size, j * size);
			c.generateChunk();
			chunks.push_back(c);
		}
	}
}

Chunk* WorldGeneration::displayWorld() {
	return chunks[0].displayChunk();
}
WorldGeneration::~WorldGeneration()
{
}
