#include "ChunkGenerator.h"

ChunkGenerator::ChunkGenerator(int xAxis, int zAxis, int depth) : xAxis(xAxis), zAxis(zAxis), depth(depth) {
	for (int x = 0; x < xAxis; x++) {
		for (int z = 0; z < zAxis; z++) {
			glm::vec3 grassPos(x, heights(x,z), z);
			for(int i = 1; i < grassPos.y + 1; i++){
				glm::vec3 dirtPos(grassPos.x, grassPos.y - i, grassPos.z);
				positions.push_back(dirtPos);
			}
			positions.push_back(grassPos);
		}
	}
}

void ChunkGenerator::displayChunk(BlockRenderer* r) {
	for (auto pos : positions) {
		r->drawBlock(pos.x, pos.y, pos.z);
	}
}

float ChunkGenerator::heights(int a, int b) {
	float* heightMap = new float[xAxis * zAxis];
	for (int x = 0; x < xAxis; x++) {
		for (int z = 0; z < zAxis; z++) {
			heightMap[x * z] = (int)calculateHeights(x, z);
		}
	}
	return heightMap[a * b];
}

float ChunkGenerator::calculateHeights(int a, int b) {
	float xCoord = (float)a / xAxis;
	float yCoord = (float)b / zAxis;
	return pn.noise(xCoord, yCoord, 0) * depth;
}

ChunkGenerator::~ChunkGenerator()
{
}
