#include "Entity.h"



Entity::Entity(Chunk* chunk) : chunk(chunk) {
}

void Entity::generateEntity(int x, int y, int z, entityType type) {
	xPos = x;
	yPos = y;
	zPos = z;

	if (type == Oak_Tree) spawnOak();
	else if (type == Birch_Tree) spawnBirch();
	else if (type == Cactus_Plant) spawnCactus();
}

//macro for self checking in nested for loops
#define IS_SELF x == 0 && y == 0 && z == 0

void Entity::spawnOak() const {
	for (int i = 1; i < treeLength + 1; i++) {
		chunk->addBlock(xPos, yPos + i, zPos, blockType::OakLog);
	}
	for (int x = -2; x < 3; ++x) {
		for (int y = 0; y < 2; y++) {
			for (int z = -2; z < 3; z++) {
				if (IS_SELF) continue;
				chunk->addBlock(xPos + x, treeLength + yPos + y, zPos + z, blockType::OakLeaf);
			}
		}
	}
	for (int x = -1; x < 2; ++x) {
		for (int y = 0; y < 1; y++) {
			for (int z = -1; z < 2; z++) {
				chunk->addBlock(xPos + x, treeLength + yPos + y + 2, zPos + z, blockType::OakLeaf);
			}
		}
	}
}

void Entity::spawnBirch() const {
	for (int i = 1; i < treeLength + 1; i++) {
		chunk->addBlock(xPos, yPos + i, zPos, blockType::BirchLog);
	}
	for (int x = -2; x < 3; ++x) {
		for (int y = 0; y < 2; y++) {
			for (int z = -2; z < 3; z++) {
				if (ifCorner(x, z, 2) || IS_SELF) continue;
				chunk->addBlock(xPos + x, treeLength + yPos + y, zPos + z, blockType::BirchLeaf);
			}
		}
	}
	for (int x = -1; x < 2; ++x) {
		for (int y = 0; y < 1; y++) {
			for (int z = -1; z < 2; z++) {
				if (ifCorner(x, z, 1)) continue;
				chunk->addBlock(xPos + x, treeLength + yPos + y + 2, zPos + z, blockType::BirchLeaf);
			}
		}
	}
}
void Entity::spawnCactus() const {
	chunk->addBlock(xPos, yPos + cactusLength - 1, zPos, blockType::CactusTop);
	for (int i = 0; i < cactusLength - 1; i++) {
		chunk->addBlock(xPos, yPos + i, zPos, blockType::CactusMiddle);
	}
}

bool Entity::ifCorner(int a, int b, int t) const {
	if (a == -t && b == -t ||
		a ==  t && b == -t ||
		a == -t && b ==  t ||
		a ==  t && b ==  t) return true;
	return false;
}

bool Entity::isNextToEntity(const Chunk& chunk) const {
	for (int x = -1; x < 2; ++x) {
		for (int y = -1; y < 2; ++y) {
			for (int z = -1; z < 2; ++z) {
				if (IS_SELF) continue;
				if (chunk.getBlock(xPos + x, yPos + y, zPos + z).getType() == CactusMiddle ||
					chunk.getBlock(xPos + x, yPos + y, zPos + z).getType() == BirchLog ||
					chunk.getBlock(xPos + x, yPos + y, zPos + z).getType() == OakLog) {
					return true;
				}
			}
		}
	}
	return false;
}

Entity::~Entity() {
}
