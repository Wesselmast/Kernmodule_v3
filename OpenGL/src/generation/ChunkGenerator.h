#pragma once
#include <memory>
#include "PerlinNoise.h"
#include "Chunk.h"
#include "Entity.h"

enum Biome {
	Forest, Desert
};

class ChunkGenerator {
private:
	const int density = 85;
	const int middleDepth = 3;
	const int airLayer = 20;
private:
	int startX, startZ, size, height, xPos, zPos;
	int waterPlane;
	int amtOfOctaves;
	int heightScale;
	BlockType topType, middleType, bottomType;
	std::unique_ptr<PerlinNoise> perlinNoise;
private:
	int calculateHeights(int a, int b) const;
public:
	ChunkGenerator(int size, int height, int amtOfOctaves);
	Chunk* generateChunk(int oX, int oY, float heightScale, Biome type);
	~ChunkGenerator();
};

