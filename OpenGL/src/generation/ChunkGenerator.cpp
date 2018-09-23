#include "ChunkGenerator.h"

ChunkGenerator::ChunkGenerator(int width, int length, int height) {
	chunkSize.x = width;
	chunkSize.y = height;
	chunkSize.z = length;

	perlinOffsetX = rand() % 9999;
	perlinOffsetY = rand() % 9999;
}

void ChunkGenerator::generateChunk() {
	for (int x = chunkOffset.x; x < chunkSize.x + chunkOffset.x; ++x) {
		for (int z = chunkOffset.y; z < chunkSize.z + chunkOffset.y; ++z) {
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

void ChunkGenerator::displayChunk(BlockRenderer* r) {
	for (auto pos : gPositions) {
		r->drawBlock(pos.x, pos.y, pos.z);
	}
	for (auto pos : dPositions) {
		r->drawBlock(pos.x, pos.y, pos.z);
	}
}

float ChunkGenerator::heights(int a, int b) {
	std::vector<std::vector<float>> heightMap;
	heightMap.resize(chunkSize.x + chunkOffset.x);
	for (int x = chunkOffset.x; x < heightMap.size(); ++x) {
		heightMap[x].resize(chunkSize.z + chunkOffset.y);
		for (int z = chunkOffset.y; z < heightMap[x].size(); ++z) {
			heightMap[x][z] = (int)calculateHeights(x, z);
		}
	}
	return heightMap[a][b];
}	

double ChunkGenerator::calculateHeights(int a, int b) {
	float xCoord = (float)a / chunkSize.x + perlinOffsetX;
	float yCoord = (float)b / chunkSize.z + perlinOffsetY;
	return pn.noise(xCoord, yCoord) * chunkSize.y;
}

ChunkGenerator::~ChunkGenerator()
{
	
}
