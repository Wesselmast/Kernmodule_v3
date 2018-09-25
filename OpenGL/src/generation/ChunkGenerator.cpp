#include "ChunkGenerator.h"

ChunkGenerator::ChunkGenerator(int size, int height) : size(size), height(height) {
	perlinOffset.x = rand() % 9999;
	perlinOffset.y = rand() % 9999;

	chunk = new Chunk(size, 0, 0, 0);
}

void ChunkGenerator::setChunkOffset(int oX, int oY) {
	chunkOffset.x = oX;
	chunkOffset.y = oY;
}

Chunk* ChunkGenerator::displayChunk() {
	generateChunk();

	for (auto pos : gPositions) {
		chunk->AddBlock(pos->x, pos->y, pos->z, blockType::Grass);
	}
	for (auto pos : dPositions) {
		chunk->AddBlock(pos->x, pos->y, pos->z, blockType::Dirt);
	}
	for (auto pos : sPositions) {
		chunk->AddBlock(pos->x, pos->y, pos->z, blockType::Stone);
	}
	for (auto pos : logPositions) {
		chunk->AddBlock(pos->x, pos->y, pos->z, blockType::Log);
	}
	for (auto pos : leafPositions) {
		chunk->AddBlock(pos->x, pos->y, pos->z, blockType::Leaf);
	}
	return chunk;
}

void ChunkGenerator::generateChunk() {
	for (int x = chunkOffset.x; x < size + chunkOffset.x; ++x) {
		for (int z = chunkOffset.y; z < size + chunkOffset.y; ++z) {
			grassPos = new glm::vec3(x, heights(x, z), z);
			gPositions.emplace_back(grassPos);
			for (int i = 1; i < 4; ++i) {
				dirtPos = new glm::vec3(grassPos->x, grassPos->y - i, grassPos->z);
				dPositions.emplace_back(dirtPos);
			}
			for (int i = 1; i < dirtPos->y + 1; ++i) {
				stonePos = new glm::vec3(dirtPos->x, dirtPos->y - i, dirtPos->z);
				sPositions.emplace_back(stonePos);
			}
			if (z == rand() % size && x == rand() % size) {
				generateTree();
			}
		}
	}
}

void ChunkGenerator::generateTree() {
	int treeLength = rand() % 3 + 4;
	for (int i = 1; i < treeLength + 1; i++) {
		logPos = new glm::vec3(grassPos->x, grassPos->y + i, grassPos->z);
		logPositions.emplace_back(logPos);
	}
	for (int x = -2; x < 3; ++x) {
		for (int y = 0; y < 2; y++) {
			for (int z = -2; z < 3; z++) {
				leafPos = new glm::vec3(logPos->x + x, treeLength + grassPos->y + y, logPos->z + z);
				leafPositions.emplace_back(leafPos);
			}
		}
	}
	for (int x = -1; x < 2; ++x) {
		for (int y = 0; y < 1; y++) {
			for (int z = -1; z < 2; z++) {
				leafPos = new glm::vec3(logPos->x + x, treeLength + grassPos->y + y + 2, logPos->z + z);
				leafPositions.emplace_back(leafPos);
			}
		}
	}
}

float ChunkGenerator::heights(int a, int b) {
	std::vector<std::vector<float>> heightMap;
	heightMap.resize(size + chunkOffset.x);
	for (int x = chunkOffset.x; x < heightMap.size(); ++x) {
		heightMap[x].resize(size + chunkOffset.y);
		for (int z = chunkOffset.y; z < heightMap[x].size(); ++z) {
			heightMap[x][z] = (int)calculateHeights(x, z);
		}
	}
	return heightMap[a][b];
}	

double ChunkGenerator::calculateHeights(int a, int b) {
	float xCoord = (float)a / size + perlinOffset.x;
	float yCoord = (float)b / size + perlinOffset.y;
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
