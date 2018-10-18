#include "Entity.h"



Entity::Entity() {
}

void Entity::generateEntity(glm::vec3* topLayer, Chunk* chunk, entityType type) {
	xPos = topLayer->x;
	yPos = topLayer->y;
	zPos = topLayer->z;

	if (type == Oak_Tree) spawnOak(chunk);
	else if (type == Birch_Tree) spawnBirch(chunk);
	else if (type == Cactus_Plant) spawnCactus(chunk);
}

//macro for self checking in nested for loops
#define IS_SELF x == 0 && y == 0 && z == 0

void Entity::spawnOak(Chunk* chunk) {
	glm::vec3* logPos = nullptr;
	int treeLength = rand() % 3 + 4;
	for (int i = 1; i < treeLength + 1; i++) {
		logPos = new glm::vec3(xPos, yPos + i, zPos);
		chunk->AddBlock(logPos->x, logPos->y, logPos->z, blockType::OakLog);
	}
	for (int x = -2; x < 3; ++x) {
		for (int y = 0; y < 2; y++) {
			for (int z = -2; z < 3; z++) {
				if (IS_SELF) continue;
				chunk->AddBlock(logPos->x + x, treeLength + yPos + y, logPos->z + z, blockType::OakLeaf);
			}
		}
	}
	for (int x = -1; x < 2; ++x) {
		for (int y = 0; y < 1; y++) {
			for (int z = -1; z < 2; z++) {
				chunk->AddBlock(logPos->x + x, treeLength + yPos + y + 2, logPos->z + z, blockType::OakLeaf);
			}
		}
	}
	delete logPos;
}

void Entity::spawnBirch(Chunk* chunk) {
	glm::vec3* logPos = nullptr;
	int treeLength = rand() % 3 + 4;
	for (int i = 1; i < treeLength + 1; i++) {
		logPos = new glm::vec3(xPos, yPos + i, zPos);
		chunk->AddBlock(logPos->x, logPos->y, logPos->z, blockType::BirchLog);
	}
	for (int x = -2; x < 3; ++x) {
		for (int y = 0; y < 2; y++) {
			for (int z = -2; z < 3; z++) {
				if (ifCorner(x, z, 2) || IS_SELF) continue;
				chunk->AddBlock(logPos->x + x, treeLength + yPos + y, logPos->z + z, blockType::BirchLeaf);
			}
		}
	}
	for (int x = -1; x < 2; ++x) {
		for (int y = 0; y < 1; y++) {
			for (int z = -1; z < 2; z++) {
				if (ifCorner(x, z, 1)) continue;
				chunk->AddBlock(logPos->x + x, treeLength + yPos + y + 2, logPos->z + z, blockType::BirchLeaf);
			}
		}
	}
	delete logPos;
}
void Entity::spawnCactus(Chunk * chunk) {
	for (int i = 0; i < cactusLength; i++) {
		chunk->AddBlock(xPos, yPos + i, zPos, blockType::Cactus);
	}
}

bool Entity::ifCorner(int a, int b, int t) {
	if (a == -t && b == -t ||
		a ==  t && b == -t ||
		a == -t && b ==  t ||
		a ==  t && b ==  t) return true;
	return false;
}

Entity::~Entity() {
}
