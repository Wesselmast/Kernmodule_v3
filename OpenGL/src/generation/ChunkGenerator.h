#pragma once
#include <iostream>
#include <vector>
#include "BlockRenderer.h"
#include "WesselPerlinNoise.h"
#include "glm/gtc/matrix_transform.hpp"

class ChunkGenerator
{
private:
	float perlinOffsetX, perlinOffsetY;
	glm::vec3 chunkSize;
	glm::vec2 chunkOffset;
	std::vector<glm::vec3> gPositions;
	std::vector<glm::vec3> dPositions;
	WesselPerlinNoise pn;
private:
	float heights(int a, int b);
	double calculateHeights(int a, int b);
public:
	ChunkGenerator(int width, int length, int heigth);
	void displayChunk(BlockRenderer* r);
	void generateChunk();
	void setChunkOffset(int oX, int oY);
	~ChunkGenerator();
};

