#pragma once
#include "ChunkGenerator.h"
#include <vector>

class WorldGeneration
{
private:
	std::vector<ChunkGenerator> chunks;
public:
	WorldGeneration(int amountOfChunks, int width, int length, int height);
	void displayWorld(BlockRenderer* r);
	~WorldGeneration();
};

