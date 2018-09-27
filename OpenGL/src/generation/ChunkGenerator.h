#pragma once
#include <vector>
#include "WesselPerlinNoise.h"
#include "Chunk.h"
#include "glm/gtc/matrix_transform.hpp"

class ChunkGenerator
{
private:
	int treeDensity = 100;
	int startX, startY;
	glm::vec3* grassPos;
	glm::vec3* dirtPos;
	glm::vec3* stonePos;
	glm::vec3* logPos;
	glm::vec3* leafPos;
	WesselPerlinNoise pn;
	Chunk* chunk;
private:
	float heights(int a, int b, int xPos, int yPos);
	double calculateHeights(int a, int b, int xPos, int yPos);
	void generateTree();
public:
	int size, height;
public:
	ChunkGenerator(int size, int height);
	Chunk* generateChunk(int oX, int oY);
	~ChunkGenerator();
};

