#include "WorldGeneration.h"

WorldGeneration::WorldGeneration(int size, int height)
{
	ChunkGenerator c(size,height);

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			c.setChunkOffset(i * size, j * size);
			chunks.emplace_back(c);
		}
	}
}

Chunk* WorldGeneration::displayWorld(int index) {
	return chunks[index].displayChunk();
}
WorldGeneration::~WorldGeneration()
{
}
