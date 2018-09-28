#pragma once
#include <vector>
#include "WesselPerlinNoise.h"
#include "Chunk.h"
#include "glm/gtc/matrix_transform.hpp"

class ChunkGenerator
{
private: //section of world customisation
	int treeLength = rand() % 3 + 4;
	int treeDensity = 80;
	int dirtLayer = 4;
private: //section for private variables
	int startX, startZ, size, height, xPos, zPos;
	glm::vec3* grassPos;
	glm::vec3* dirtPos;
	glm::vec3* stonePos;
	glm::vec3* logPos;
	glm::vec3* leafPos;
	WesselPerlinNoise pn;
	Chunk* chunk;
private: //section for private functions
	float heights(int a, int b);
	double calculateHeights(int a, int b);
	void generateTree();
public: //section for public functions
	ChunkGenerator(int size, int height);
	Chunk* generateChunk(int oX, int oY);
	~ChunkGenerator();
};

