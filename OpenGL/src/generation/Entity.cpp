#include "Entity.h"



Entity::Entity() {
}

void Entity::generateEntity(int x, int y, int z, Chunk* chunk, entityType type) {
	xPos = x;
	yPos = y;
	zPos = z;

	if (type == Oak_Tree) spawnOak(chunk);
	else if (type == Birch_Tree) spawnBirch(chunk);
	else if (type == Cactus_Plant) spawnCactus(chunk);
}

//macro for self checking in nested for loops
#define IS_SELF x == 0 && y == 0 && z == 0

void Entity::spawnOak(Chunk* chunk) {
	int logPos = 0;
	int treeLength = rand() % 3 + 4;
	for (int i = 1; i < treeLength + 1; i++) {
		chunk->AddBlock(xPos, logPos, zPos, blockType::OakLog);
		logPos = yPos + i;
	}
	for (int x = -2; x < 3; ++x) {
		for (int y = 0; y < 2; y++) {
			for (int z = -2; z < 3; z++) {
				if (IS_SELF) continue;
				chunk->AddBlock(xPos + x, treeLength + yPos + y, zPos + z, blockType::OakLeaf);
			}
		}
	}
	for (int x = -1; x < 2; ++x) {
		for (int y = 0; y < 1; y++) {
			for (int z = -1; z < 2; z++) {
				chunk->AddBlock(xPos + x, treeLength + yPos + y + 2, zPos + z, blockType::OakLeaf);
			}
		}
	}
}

void Entity::spawnBirch(Chunk* chunk) {
	int logPos = 0;
	int treeLength = rand() % 3 + 4;
	for (int i = 1; i < treeLength + 1; i++) {
		chunk->AddBlock(xPos, logPos, zPos, blockType::BirchLog);
		logPos = yPos + i;
	}
	for (int x = -2; x < 3; ++x) {
		for (int y = 0; y < 2; y++) {
			for (int z = -2; z < 3; z++) {
				if (ifCorner(x, z, 2) || IS_SELF) continue;
				chunk->AddBlock(xPos + x, treeLength + yPos + y, zPos + z, blockType::BirchLeaf);
			}
		}
	}
	for (int x = -1; x < 2; ++x) {
		for (int y = 0; y < 1; y++) {
			for (int z = -1; z < 2; z++) {
				if (ifCorner(x, z, 1)) continue;
				chunk->AddBlock(xPos + x, treeLength + yPos + y + 2, zPos + z, blockType::BirchLeaf);
			}
		}
	}
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
