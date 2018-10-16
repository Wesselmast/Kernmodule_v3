#pragma once
#include <memory>
#include "WesselPerlinNoise.h"
#include "Chunk.h"
#include "Entity.h"
#include "glm/gtc/matrix_transform.hpp"

enum biome {
	Forest, Desert
};

class ChunkGenerator {
private: //section for constants
	const int density = 85;
	const int middleDepth = 3;
	const int airLayer = 20;
private: //section for private variables
	int startX, startZ, size, height, xPos, zPos;
	int waterPlane;
	int amtOfOctaves;
	int heightScale;
	glm::vec3* topLayer;
	glm::vec3* middleLayer; 
	glm::vec3* bottomLayer;
	blockType topType, middleType, bottomType;
	WesselPerlinNoise pn;
private: //section for private functions
	int heights(int a, int b);
	double calculateHeights(int a, int b);
	bool isNextToEntity(Chunk* chunk, glm::vec3* topLayer);
public: //section for public functions
	ChunkGenerator(int size, int height, int amtOfOctaves);
	Chunk* generateChunk(int oX, int oY, float heightScale, biome type);
	~ChunkGenerator();
};

