#pragma once
#include <vector>
#include "ChunkGenerator.h"
#include "Camera.h"
#include "ChunkManager.h"

class WorldGeneration
{
private: //section for private variables
	int size, height, amtOfChunks, num;
	ChunkGenerator* chunkGen;
	std::vector<Chunk*> chunks;
	ChunkManager* man;
	Camera* player;
public: //section for public functions
	WorldGeneration(int size, int height, int amtOfChunks, int amtOfOctaves, ChunkManager* man, Camera* player);
	std::vector<Chunk*> generateWorld();
	void updateChunks();
	std::vector<glm::vec2> getNeighbours();
	~WorldGeneration();
};