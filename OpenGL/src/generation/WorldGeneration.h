#pragma once
#include "ChunkGenerator.h"
#include <vector>

class WorldGeneration
{
private:
	std::vector<ChunkGenerator> chunks;
public:
	WorldGeneration(int chunk, int height);
	Chunk* displayWorld(int index);
	~WorldGeneration();
};

