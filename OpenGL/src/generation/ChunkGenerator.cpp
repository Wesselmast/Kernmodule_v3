#include "ChunkGenerator.h"

ChunkGenerator::ChunkGenerator(int size, int height, int amtOfOctaves) : size(size), height(height), amtOfOctaves(amtOfOctaves) {
	//get a random starting position for the perlin noise
	startX = rand() % 9999;
	startZ = rand() % 9999;

	if (heightScale < 1.0f) {
		heightScale = 1.0f;
	}
}

Chunk* ChunkGenerator::generateChunk(int xPos, int zPos, float heightScale, biome type) {
	chunk = new Chunk(size, height, xPos, 0, zPos);
	this->heightScale = heightScale;
	this->xPos = xPos;
	this->zPos = zPos;

	if (type == Forest) generateForest();
	else if (type == Desert) generateDesert();
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

Chunk* ChunkGenerator::generateDesert() {
	Plant* cactus = new Plant();

	for (int x = 0; x < size; ++x) {
		for (int z = 0; z < size; ++z) {
			//make a vector3 containing the grass positions (with pnoise heightmap)
			//the other blocks are spawned below/above the grass layer
			topLayer = new glm::vec3(x, heights(x, z), z);
			chunk->AddBlock(topLayer->x, topLayer->y, topLayer->z, blockType::Sand);
			for (int i = 1; i < middleDepth; ++i) {
				middleLayer = new glm::vec3(topLayer->x, topLayer->y - i, topLayer->z);
				chunk->AddBlock(middleLayer->x, middleLayer->y, middleLayer->z, blockType::Sand);
			}
			for (int i = 1; i < middleLayer->y + 1; ++i) {
				bottomLayer = new glm::vec3(middleLayer->x, middleLayer->y - i, middleLayer->z);
				chunk->AddBlock(bottomLayer->x, bottomLayer->y, bottomLayer->z, blockType::Sand);
			}

			//get your chance at a cactus!
			if (rand() % density == 1) {
				cactus->generatePlant(topLayer, chunk, blockType::Cactus);
			}
		}
	}
	delete cactus;
	return chunk;
}

Chunk* ChunkGenerator::generateForest() {
	Tree* tree = new Tree();

	for (int x = 0; x < size; ++x) {
		for (int z = 0; z < size; ++z) {
			//make a vector3 containing the grass positions (with pnoise heightmap)
			//the other blocks are spawned below/above the grass layer
			topLayer = new glm::vec3(x, heights(x, z), z);
			chunk->AddBlock(topLayer->x, topLayer->y, topLayer->z, blockType::Grass);
			for (int i = 1; i < middleDepth; ++i) {
				middleLayer = new glm::vec3(topLayer->x, topLayer->y - i, topLayer->z);
				chunk->AddBlock(middleLayer->x, middleLayer->y, middleLayer->z, blockType::Dirt);
			}
			for (int i = 1; i < middleLayer->y + 1; ++i) {
				bottomLayer = new glm::vec3(middleLayer->x, middleLayer->y - i, middleLayer->z);
				chunk->AddBlock(bottomLayer->x, bottomLayer->y, bottomLayer->z, blockType::Stone);
			}

			//get your chance at a tree!
			if (rand() % density == 1) {
				tree->generateTree(topLayer, chunk, treeType::Oak);
			}
		}
	}
	delete tree;
	return chunk;
}

ChunkGenerator::~ChunkGenerator() {
	delete chunk;
	delete topLayer;
	delete middleLayer;
	delete bottomLayer;
}
