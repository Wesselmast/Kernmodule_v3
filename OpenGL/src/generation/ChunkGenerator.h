#pragma once
#include <memory>
#include "PerlinNoise.h"
#include "Chunk.h"
#include "Entity.h"

enum biome {
	Forest, Desert
};

class ChunkGenerator {
private: //section for private constant variables
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
	int calculateHeights(int a, int b) const;
public: //section for public functions
	ChunkGenerator(int size, int height, int amtOfOctaves);
	Chunk* generateChunk(int oX, int oY, float heightScale, biome type);
	~ChunkGenerator();
};

