#pragma once
#include <vector>
#include "WesselPerlinNoise.h"
#include "Chunk.h"
#include "Tree.h"
#include "Plant.h"
#include "glm/gtc/matrix_transform.hpp"

enum biome {
	Forest, Desert
};

class ChunkGenerator {
private: //section of world customisation
	int density = 65;
	int middleDepth = 3;
	int amtOfOctaves;
	int heightScale;
private: //section for private variables
	int startX, startZ, size, height, xPos, zPos;
	glm::vec3* topLayer;
	glm::vec3* middleLayer;
	glm::vec3* bottomLayer;
	blockType topType, middleType, bottomType;
	Chunk* chunk;
	WesselPerlinNoise pn;
private: //section for private functions
	int heights(int a, int b);
	double calculateHeights(int a, int b);
public: //section for public functions
	ChunkGenerator(int size, int height, int amtOfOctaves);
	Chunk* generateChunk(int oX, int oY, float heightScale, biome type);
	~ChunkGenerator();
};

