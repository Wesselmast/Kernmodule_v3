#pragma once
#include <vector>
#include "ChunkGenerator.h"

class WorldGeneration
{
private:
	ChunkGenerator* chunkGen;
	int size, height, amtOfChunks;
	int incr = 0;
	int deleteIndex;
public:
	std::vector<Chunk*> chunks;
	void deleteChunk();
	void addChunk(int x, int z);
	bool chunkExists(int x, int z);
public:
	WorldGeneration(int size, int height, int amtOfChunks);
	std::vector<Chunk*> generateWorld();
	void updateChunk(int xPos, int zPos);
	int getAmount();
	~WorldGeneration();
};