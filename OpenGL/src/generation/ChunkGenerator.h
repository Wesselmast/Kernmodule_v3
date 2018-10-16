#pragma once
#include <memory>
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
	const int density = 65;
	const int middleDepth = 3;
	const int airLayer = 20;
	int waterPlane;
	int amtOfOctaves;
	int heightScale;
private: //section for private variables
	int startX, startZ, size, height, xPos, zPos;
	glm::vec3* topLayer;
	glm::vec3* middleLayer; 
	glm::vec3* bottomLayer;
	blockType topType, middleType, bottomType;
	WesselPerlinNoise pn;
private: //section for private functions
	int heights(int a, int b);
	double calculateHeights(int a, int b);
public: //section for public functions
	ChunkGenerator(int size, int height, int amtOfOctaves);
	Chunk* generateChunk(int oX, int oY, float heightScale, biome type);
	~ChunkGenerator();
};

