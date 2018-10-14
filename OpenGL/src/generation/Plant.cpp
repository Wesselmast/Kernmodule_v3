#include "Plant.h"

Plant::Plant()
{
}

void Plant::generatePlant(glm::vec3 * grassPos, Chunk * chunk, blockType type) {
	xPos = grassPos->x;
	yPos = grassPos->y;
	zPos = grassPos->z;

	if (type == Cactus) {
		for (int i = 0; i < cactusLength; i++) {
			chunk->AddBlock(xPos, yPos + i, zPos, blockType::Cactus);
		}
	}
}

Plant::~Plant()
{
}
