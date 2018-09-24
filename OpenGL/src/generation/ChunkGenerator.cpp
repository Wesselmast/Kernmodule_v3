#include "ChunkGenerator.h"

ChunkGenerator::ChunkGenerator(int size, int height) : size(size), height(height) {
	perlinOffsetX = rand() % 9999;
	perlinOffsetY = rand() % 9999;

	chunk = new Chunk(size,0,0,0);
}

void ChunkGenerator::generateChunk() {
	for (int x = chunkOffset.x; x < size + chunkOffset.x; ++x) {
		for (int z = chunkOffset.y; z < size + chunkOffset.y; ++z) {
			glm::vec3 grassPos(x, heights(x, z), z);
			gPositions.push_back(grassPos);
			for (int i = 1; i < grassPos.y + 1; ++i) {
				glm::vec3 dirtPos(grassPos.x, grassPos.y - i, grassPos.z);
				dPositions.push_back(dirtPos);
			}
		}
	}
}

void ChunkGenerator::setChunkOffset(int oX, int oY) {
	chunkOffset.x = oX;
	chunkOffset.y = oY;
}

Chunk* ChunkGenerator::displayChunk() {
	for (auto pos : gPositions) {
		chunk->AddBlock(pos.x, pos.y, pos.z, blockType::Grass);
	}
	for (auto pos : dPositions) {
		chunk->AddBlock(pos.x, pos.y, pos.z, blockType::Dirt);
	}
	return chunk;
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
	float xCoord = (float)a / size + perlinOffsetX;
	float yCoord = (float)b / size + perlinOffsetY;
	return pn.noise(xCoord, yCoord) * height;
}

ChunkGenerator::~ChunkGenerator()
{
	
}
