#include "ChunkGenerator.h"

ChunkGenerator::ChunkGenerator(int size, int height) : size(size), height(height) {
	startX = rand() % 9999;
	startY = rand() % 9999;
}

Chunk* ChunkGenerator::generateChunk(int oX, int oY) {
	chunk = new Chunk(size, height, oX, 0, oY);

	for (int x = 0; x < size; ++x) {
		for (int z = 0; z < size; ++z) {
			grassPos = new glm::vec3(x, heights(x, z,oX,oY), z);
			chunk->AddBlock(grassPos->x, grassPos->y, grassPos->z, blockType::Grass);
			for (int i = 1; i < 4; ++i) {
				dirtPos = new glm::vec3(grassPos->x, grassPos->y - i, grassPos->z);
				chunk->AddBlock(dirtPos->x, dirtPos->y, dirtPos->z, blockType::Dirt);
			}
			for (int i = 1; i < dirtPos->y + 1; ++i) {
				stonePos = new glm::vec3(dirtPos->x, dirtPos->y - i, dirtPos->z);
				chunk->AddBlock(stonePos->x, stonePos->y, stonePos->z, blockType::Stone);
			}
			if (rand() % treeDensity == 1) {
				generateTree();
			}
		}
	}
	return chunk;
}

void ChunkGenerator::generateTree() {
	int treeLength = rand() % 3 + 4;
	for (int i = 1; i < treeLength + 1; i++) {
		logPos = new glm::vec3(grassPos->x, grassPos->y + i, grassPos->z);
		chunk->AddBlock(logPos->x, logPos->y, logPos->z, blockType::Log);
	}
	for (int x = -2; x < 3; ++x) {
		for (int y = 0; y < 2; y++) {
			for (int z = -2; z < 3; z++) {
				leafPos = new glm::vec3(logPos->x + x, treeLength + grassPos->y + y, logPos->z + z);
				chunk->AddBlock(leafPos->x, leafPos->y, leafPos->z, blockType::Leaf);
			}
		}
	}
	for (int x = -1; x < 2; ++x) {
		for (int y = 0; y < 1; y++) {
			for (int z = -1; z < 2; z++) {
				leafPos = new glm::vec3(logPos->x + x, treeLength + grassPos->y + y + 2, logPos->z + z);
				chunk->AddBlock(leafPos->x, leafPos->y, leafPos->z, blockType::Leaf);
			}
		}
	}
}

float ChunkGenerator::heights(int a, int b, int xPos, int yPos) {
	std::vector<std::vector<float>> heightMap;
	heightMap.resize(size);
	for (int x = 0; x < heightMap.size(); ++x) {
		heightMap[x].resize(size);
		for (int z = 0; z < heightMap[x].size(); ++z) {
			heightMap[x][z] = (int)calculateHeights(x, z, xPos, yPos);
		}
	}
	return heightMap[a][b];
}	

double ChunkGenerator::calculateHeights(int a, int b, int xPos, int yPos) {
	float xCoord = (float)a / size + (startX + (xPos/size));
	float yCoord = (float)b / size + (startY + (yPos/size));
	return pn.noise(xCoord, yCoord) * height;
}

ChunkGenerator::~ChunkGenerator() {
	delete chunk;	
	delete logPos;
	delete leafPos;
	delete grassPos;
	delete dirtPos;
	delete stonePos;
}
