#include "ChunkGenerator.h"

ChunkGenerator::ChunkGenerator(int size, int height, int amtOfOctaves, float heightScale) : size(size), height(height), amtOfOctaves(amtOfOctaves), heightScale(heightScale) {
	//get a random starting position for the perlin noise
	startX = rand() % 9999;
	startZ = rand() % 9999;

	if (heightScale < 1.0f) {
		heightScale = 1.0f;
	}
}

Chunk* ChunkGenerator::generateChunk(int oX, int oY) {
	chunk = new Chunk(size, height, oX, 0, oY);
	Tree* tree = new Tree();
	xPos = oX;
	zPos = oY;

	for (int x = 0; x < size; ++x) {
		for (int z = 0; z < size; ++z) {
			//make a vector3 containing the grass positions (with pnoise heightmap)
			//the other blocks are spawned below/above the grass layer
			grassPos = new glm::vec3(x, heights(x, z), z);
			chunk->AddBlock(grassPos->x, grassPos->y, grassPos->z, blockType::Grass);
			for (int i = 1; i < dirtLayer; ++i) {
				dirtPos = new glm::vec3(grassPos->x, grassPos->y - i, grassPos->z);
				chunk->AddBlock(dirtPos->x, dirtPos->y, dirtPos->z, blockType::Dirt);
			}
			for (int i = 1; i < dirtPos->y + 1; ++i) {
				stonePos = new glm::vec3(dirtPos->x, dirtPos->y - i, dirtPos->z);
				chunk->AddBlock(stonePos->x, stonePos->y, stonePos->z, blockType::Stone);
			}
			//get your chance at a tree!

			if (rand() % treeDensity == 1) {
				tree->generateTree(grassPos, chunk);
			}
		}
	}
	delete tree;
	return chunk;
}

int ChunkGenerator::heights(int a, int b) {
	int* heightMap = new int[size * size];
	for (int x = 0; x < size; ++x) {
		for (int z = 0; z < size; ++z) {
			heightMap[x + z * size] = (int)calculateHeights(x, z);
		}
	}
	return heightMap[a + b * size];
}	

double ChunkGenerator::calculateHeights(int a, int b) {
	//calculate the appropriate coordinates for the perlin noise
	float xCoord = (((float)a / size) + (startX + (xPos / size))) / ((float)height / heightScale);
	float zCoord = (((float)b / size) + (startZ + (zPos / size))) / ((float)height / heightScale);
	return pn.octaveNoise(xCoord, zCoord, amtOfOctaves) * height;
}

ChunkGenerator::~ChunkGenerator() {
	delete chunk;
	delete grassPos;
	delete dirtPos;
	delete stonePos;
}
