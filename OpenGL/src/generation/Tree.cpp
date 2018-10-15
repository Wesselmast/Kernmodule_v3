#include "Tree.h"



Tree::Tree() {
}

void Tree::generateTree(glm::vec3* topLayer, Chunk* chunk, treeType type) {
	xPos = topLayer->x;
	yPos = topLayer->y;
	zPos = topLayer->z;

	if (type == Oak) spawnOak(chunk);
	if (type == Birch) spawnBirch(chunk);
}

void Tree::spawnOak(Chunk* chunk) {
	treeLength = rand() % 3 + 4;
	for (int i = 1; i < treeLength + 1; i++) {
		logPos = new glm::vec3(xPos, yPos + i, zPos);
		chunk->AddBlock(logPos->x, logPos->y, logPos->z, blockType::OakLog);
	}
	for (int x = -2; x < 3; ++x) {
		for (int y = 0; y < 2; y++) {
			for (int z = -2; z < 3; z++) {
				leafPos = new glm::vec3(logPos->x + x, treeLength + yPos + y, logPos->z + z);
				chunk->AddBlock(leafPos->x, leafPos->y, leafPos->z, blockType::OakLeaf);
			}
		}
	}
	for (int x = -1; x < 2; ++x) {
		for (int y = 0; y < 1; y++) {
			for (int z = -1; z < 2; z++) {
				leafPos = new glm::vec3(logPos->x + x, treeLength + yPos + y + 2, logPos->z + z);
				chunk->AddBlock(leafPos->x, leafPos->y, leafPos->z, blockType::OakLeaf);
			}
		}
	}
}

void Tree::spawnBirch(Chunk* chunk) {
	treeLength = rand() % 3 + 4;
	for (int i = 1; i < treeLength + 1; i++) {
		logPos = new glm::vec3(xPos, yPos + i, zPos);
		chunk->AddBlock(logPos->x, logPos->y, logPos->z, blockType::BirchLog);
	}
	for (int x = -2; x < 3; ++x) {
		for (int y = 0; y < 2; y++) {
			for (int z = -2; z < 3; z++) {
				if (ifCorner(x, z, 2)) continue;
				leafPos = new glm::vec3(logPos->x + x, treeLength + yPos + y, logPos->z + z);
				chunk->AddBlock(leafPos->x, leafPos->y, leafPos->z, blockType::BirchLeaf);
			}
		}
	}
	for (int x = -1; x < 2; ++x) {
		for (int y = 0; y < 1; y++) {
			for (int z = -1; z < 2; z++) {
				if (ifCorner(x, z, 1)) continue;
				leafPos = new glm::vec3(logPos->x + x, treeLength + yPos + y + 2, logPos->z + z);
				chunk->AddBlock(leafPos->x, leafPos->y, leafPos->z, blockType::BirchLeaf);
			}
		}
	}
}

bool Tree::ifCorner(int a, int b, int t) {
	if (a == -t && b == -t ||
		a ==  t && b == -t ||
		a == -t && b ==  t ||
		a ==  t && b ==  t) return true;
	return false;
}

Tree::~Tree() {
	delete logPos;
	delete leafPos;
}
