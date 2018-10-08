#pragma once
#include <vector>
#include "WesselPerlinNoise.h"
#include "Chunk.h"
#include "Tree.h"
#include "glm/gtc/matrix_transform.hpp"

class ChunkGenerator
{
private: //section of world customisation
	int treeDensity = 65;
	int dirtLayer = 3;
	int amtOfOctaves;
	int heightScale;
private: //section for private variables
	int startX, startZ, size, height, xPos, zPos;
	glm::vec3* grassPos;
	glm::vec3* dirtPos;
	glm::vec3* stonePos;
	Chunk* chunk;
	WesselPerlinNoise pn;
private: //section for private functions
	int heights(int a, int b);
	double calculateHeights(int a, int b);
public: //section for public functions
	ChunkGenerator(int size, int height, int amtOfOctaves, float heightScale);
	Chunk* generateChunk(int oX, int oY);
	~ChunkGenerator();
};

