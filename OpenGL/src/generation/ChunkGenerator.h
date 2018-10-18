#pragma once
#include <memory>
#include "PerlinNoise.h"
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
	blockType topType, middleType, bottomType;
	std::unique_ptr<PerlinNoise> pn;
private: //section for private functions
	int heights(int a, int b);
	double calculateHeights(int a, int b);
	bool isNextToEntity(Chunk* chunk, glm::vec3* topLayer);
public: //section for public functions
	ChunkGenerator(int size, int height, int amtOfOctaves);
	Chunk* generateChunk(int oX, int oY, float heightScale, biome type);
	~ChunkGenerator();
};

