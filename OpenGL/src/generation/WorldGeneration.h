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
	bool chunkExists(int x, int z);
	void deleteChunk(int x, int z);
	void updateChunk(int xPos, int zPos);
	void addChunk(int x, int z);
	int getAmount();
	~WorldGeneration();
};