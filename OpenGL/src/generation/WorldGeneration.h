#pragma once
#include <vector>
#include "ChunkGenerator.h"
#include "Camera.h"
#include "ChunkManager.h"

class WorldGeneration {
private:
	const int biomePool = 2;
private:
	int startBiomeInterval, biomeInterval;
	int size, amtOfChunks;
	float heightScale;
	Biome type;
	ChunkGenerator* chunkGen;
	ChunkManager* man;
	Camera* player;
private:
	std::vector<glm::vec2> getNeighbours() const;
	void pickNextBiome();
public:
	WorldGeneration(ChunkManager* man, Camera* player);
	void generateWorld(int size, int height, int amtOfChunks, int amtOfOctaves, float heightScale, int chanceAtBiome);
	void updateChunks();
	~WorldGeneration();
};