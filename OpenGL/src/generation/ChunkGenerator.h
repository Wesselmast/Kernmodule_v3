#pragma once
#include <vector>
#include "WesselPerlinNoise.h"
#include "Chunk.h"
#include "glm/gtc/matrix_transform.hpp"

class ChunkGenerator
{
private:
	int size, height;
	int treeDensity = 100;
	glm::vec2 chunkOffset, perlinOffset;
	glm::vec3* grassPos;
	glm::vec3* dirtPos;
	glm::vec3* stonePos;
	glm::vec3* logPos;
	glm::vec3* leafPos;
	std::vector<glm::vec3*> gPositions, dPositions, sPositions, logPositions, leafPositions;
	WesselPerlinNoise pn;
	Chunk* chunk;
private:
	float heights(int a, int b);
	double calculateHeights(int a, int b);
	void generateTree();
	void generateChunk();
public:
	ChunkGenerator(int size, int height, int oX, int oY);
	Chunk* displayChunk();
	~ChunkGenerator();
};

