#pragma once
#include <iostream>
#include <vector>
#include "BlockRenderer.h"
#include "WesselPerlinNoise.h"
#include "Chunk.h"
#include "glm/gtc/matrix_transform.hpp"

class ChunkGenerator
{
private:
	int size, height;
	glm::vec2 chunkOffset, perlinOffset;
	glm::vec3* grassPos;
	glm::vec3* dirtPos;
	glm::vec3* stonePos;
	std::vector<glm::vec3*> gPositions, dPositions, sPositions;
	WesselPerlinNoise pn;
	Chunk* chunk;
private:
	float heights(int a, int b);
	double calculateHeights(int a, int b);
public:
	ChunkGenerator(int size, int height);
	Chunk* displayChunk();
	void generateChunk();
	void setChunkOffset(int oX, int oY);
	~ChunkGenerator();
};

