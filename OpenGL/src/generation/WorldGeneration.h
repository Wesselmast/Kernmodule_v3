#pragma once
#include <vector>
#include "ChunkGenerator.h"

class WorldGeneration
{
private: //section for private variables
	ChunkGenerator* chunkGen;
	int size, height, amtOfChunks;
	int incr = 0;
	int index;
private: //section for private functions
	void deleteChunk();
	void addChunk(int x, int z);
	bool chunkExists(int x, int z);
public: //section for public variables
	std::vector<Chunk*> chunks;
public: //section for public functions
	WorldGeneration(int size, int height, int amtOfChunks);
	std::vector<Chunk*> generateWorld();
	void updateChunk(int xIndex, int zIndex);
	int getAmount();
	~WorldGeneration();
};