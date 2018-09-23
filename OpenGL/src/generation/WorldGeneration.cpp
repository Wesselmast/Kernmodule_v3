#include "WorldGeneration.h"

WorldGeneration::WorldGeneration(int amountOfChunks, int width, int length, int height)
{
	ChunkGenerator c(width,length,height);

	for (int i = 0; i < amountOfChunks; ++i) {
		for (int j = 0; j < amountOfChunks; ++j) {
			c.setChunkOffset(i * width, j * length);
			c.generateChunk();
		}
	}
	chunks.push_back(c);
}

void WorldGeneration::displayWorld(BlockRenderer* r) {
	for (int i = 0; i < chunks.size(); ++i) {
		chunks[i].displayChunk(r);
	}
}
WorldGeneration::~WorldGeneration()
{
}
