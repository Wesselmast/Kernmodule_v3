#pragma once
#include <vector>
#include "ChunkGenerator.h"

class WorldGeneration
{
private:
	std::vector<Chunk*> chunks;
	ChunkGenerator* chunkGen;
	int size, height, amtOfChunks;
public:
	WorldGeneration(int size, int height, int amtOfChunks);
	std::vector<Chunk*> generateWorld();
	int getAmount();
	~WorldGeneration();
};