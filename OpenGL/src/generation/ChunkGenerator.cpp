#include "ChunkGenerator.h"

ChunkGenerator::ChunkGenerator(int size, int height, int amtOfOctaves) : size(size), height(height + airLayer), amtOfOctaves(amtOfOctaves) {
	//get a random starting position for the perlin noise
	startX = rand() % 9999;
	startZ = rand() % 9999;
	pn = std::make_unique<PerlinNoise>();
}

Chunk* ChunkGenerator::generateChunk(int xPos, int zPos, float heightScale, biome type) {
	Chunk* chunk = new Chunk(size, height, xPos, 0, zPos);
	std::unique_ptr<Entity> entity = std::make_unique<Entity>();

	if (heightScale < 1.0f) heightScale = 1.0f;

	this->heightScale = heightScale;
	this->xPos = xPos;
	this->zPos = zPos;

	waterPlane = height / 5;

	if (type == Desert) topType = Sand, middleType = Sand, bottomType = Stone; 
	if (type == Forest) topType = Grass, middleType = Dirt, bottomType = Stone;

	for (int x = 0; x < size; ++x) {
		for (int z = 0; z < size; ++z) {
			//air layer section
			for (int i = -airLayer; i < 1; ++i) {
				chunk->AddBlock(x, height + i, z, blockType::Air);
			}

			//top layer section
			int y = heights(x, z);
			chunk->AddBlock(x, y, z, topType);

			//middle layer section
			int middleLayer = 0;
			for (int i = 1; i < middleDepth + 1; ++i) {
				middleLayer = y - i;
				chunk->AddBlock(x, middleLayer, z, middleType);
			}

			//bottom layer section
			for (int i = 1; i < middleLayer + 1; ++i) {
				chunk->AddBlock(x, middleLayer - i, z, bottomType);
			}

			//entity spawning section
			if (rand() % density == 1 && y > waterPlane && !isNextToEntity(chunk, x, y ,z)) {
				if (type == Desert) entity->generateEntity(x, y, z, chunk, entityType::Cactus_Plant);
				if (type == Forest && topType == Grass) {
					if (rand() % 2 == 1) entity->generateEntity(x, y, z, chunk, entityType::Oak_Tree);
					else entity->generateEntity(x, y, z, chunk, entityType::Birch_Tree);
				}
			}

			//bedrock & water spawning section
			chunk->AddBlock(x, -1, z, blockType::Bedrock);
			if (chunk->GetBlock(x, waterPlane, z).getType() == Air) {
				chunk->AddBlock(x, waterPlane, z, blockType::Water);
			}
		}
	}
	return chunk;
}

int ChunkGenerator::heights(int a, int b) {
	int* heightMap = new int[size * size];
	for (int x = 0; x < size; ++x) {
		for (int z = 0; z < size; ++z) {
			heightMap[x + z * size] = std::round(calculateHeights(x, z));
		}
	}
	return heightMap[a + b * size];
}	

double ChunkGenerator::calculateHeights(int a, int b) {
	float xCoord = (((float)a / size) + (startX + (xPos / size))) / ((float)(height - airLayer) / heightScale);
	float zCoord = (((float)b / size) + (startZ + (zPos / size))) / ((float)(height - airLayer) / heightScale);
	return pn->octaveNoise(xCoord, zCoord, amtOfOctaves) * (height - airLayer);
}

bool ChunkGenerator::isNextToEntity(Chunk* chunk, int xPos, int yPos, int zPos) {
	for (int x = -1; x < 2; ++x) {
		for (int y = -1; y < 2; ++y) {
			for (int z = -1; z < 2; ++z) {
				if (x == 0 && y == 0 && z == 0) continue;
				//hard-coded at the moment, fine for this project but could be done better
				if (chunk->GetBlock(xPos + x, yPos+ y, zPos + z).getType() == Cactus ||
					chunk->GetBlock(xPos + x, yPos + y, zPos + z).getType() == BirchLog ||
					chunk->GetBlock(xPos + x, yPos + y, zPos + z).getType() == OakLog) {
					return true;
				}
			}
		}
	}
	return false;
}

ChunkGenerator::~ChunkGenerator() {
}
