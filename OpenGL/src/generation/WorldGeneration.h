#pragma once
#include <vector>
#include "ChunkGenerator.h"

class WorldGeneration
{
private: //section for private variables
	ChunkGenerator* chunkGen;
	int size, height, amtOfChunks;
	std::vector<Chunk*> chunks;
public: //section for public functions
	WorldGeneration(int size, int height, int amtOfChunks);
	std::vector<Chunk*> generateWorld();
	~WorldGeneration();
};