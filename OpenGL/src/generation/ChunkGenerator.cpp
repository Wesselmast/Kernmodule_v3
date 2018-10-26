#include "ChunkGenerator.h"

ChunkGenerator::ChunkGenerator(int size, int height, int amtOfOctaves) : size(size), height(height + airLayer), amtOfOctaves(amtOfOctaves) {
	//get random starting position for perlin noise
	pn = std::make_unique<PerlinNoise>();
	startX = rand() % 9999;
	startZ = rand() % 9999;

	waterPlane = this->height / 5;
	if (heightScale < 1.0f) heightScale = 1.0f;
}

Chunk* ChunkGenerator::generateChunk(int xPos, int zPos, float heightScale, biome type) {
	Chunk* chunk = new Chunk(size, height, xPos, 0, zPos);
	std::unique_ptr<Entity> entity = std::make_unique<Entity>(chunk);

	this->heightScale = heightScale;
	this->xPos = xPos;
	this->zPos = zPos;

	if (type == Desert) topType = Sand, middleType = Sand, bottomType = Stone; 
	if (type == Forest) topType = Grass, middleType = Dirt, bottomType = Stone;

	for (int x = 0; x < size; ++x) {
		for (int z = 0; z < size; ++z) {
			//air layer section
			for (int i = -airLayer; i < 1; ++i) {
				chunk->addBlock(x, height + i, z, blockType::Air);
			}

			//top layer section
			const int y = calculateHeights(x, z);
			chunk->addBlock(x, y, z, topType);

			//middle layer section
			int middleLayer = 0;
			for (int i = 1; i < middleDepth + 1; ++i) {
				middleLayer = y - i;
				chunk->addBlock(x, middleLayer, z, middleType);
			}

			//bottom layer section
			for (int i = 1; i < middleLayer + 1; ++i) {
				chunk->addBlock(x, middleLayer - i, z, bottomType);
			}

			//entity spawning section
			if (rand() % density == 1 && y > waterPlane && !entity->isNextToEntity(*chunk)) {
				if (type == Desert) entity->generateEntity(x, y, z, entityType::Cactus_Plant);
				if (type == Forest) {
					if (rand() % 2 == 1) entity->generateEntity(x, y, z, entityType::Oak_Tree);
					else entity->generateEntity(x, y, z, entityType::Birch_Tree);
				}
			}

			//bedrock & water spawning section
			chunk->addBlock(x, -1, z, blockType::Bedrock);
			if (chunk->getBlock(x, waterPlane, z).getType() == Air) {
				chunk->addBlock(x, waterPlane, z, blockType::Water);
			}
		}
	}
	return chunk;
}

//calculate the heightmap for the terrain
int ChunkGenerator::calculateHeights(int a, int b) const {
	float xCoord = (((float)a / size) + (startX + (xPos / size))) / ((float)(height - airLayer) / heightScale);
	float zCoord = (((float)b / size) + (startZ + (zPos / size))) / ((float)(height - airLayer) / heightScale);
	return std::round(pn->octaveNoise(xCoord, zCoord, amtOfOctaves) * (height - airLayer));
}

ChunkGenerator::~ChunkGenerator() {
}
