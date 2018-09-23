#pragma once
#include <iostream>
#include <vector>
#include "BlockRenderer.h"
#include "PerlinNoise.h"
#include "glm/gtc/matrix_transform.hpp"



class ChunkGenerator
{
private:
	int xAxis, zAxis, depth;
	std::vector<glm::vec3> positions; 
	PerlinNoise pn;
private:
	float heights(int a, int b);
	float calculateHeights(int a, int b);
public:
	ChunkGenerator(int xAxis, int zAxis, int depth);
	void displayChunk(BlockRenderer* r);
	~ChunkGenerator();
};

