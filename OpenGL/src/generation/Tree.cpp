#include "Tree.h"

Tree::Tree() {
}

void Tree::generateTree(glm::vec3* topLayer, Chunk* chunk, treeType type) {
	xPos = topLayer->x;
	yPos = topLayer->y;
	zPos = topLayer->z;

	if (type == Oak) {
		treeLength = rand() % 3 + 4;
		for (int i = 1; i < treeLength + 1; i++) {
			logPos = new glm::vec3(xPos, yPos + i, zPos);
			chunk->AddBlock(logPos->x, logPos->y, logPos->z, blockType::OakLog);
		}
		//generate the initial grass blob
		for (int x = -2; x < 3; ++x) {
			for (int y = 0; y < 2; y++) {
				for (int z = -2; z < 3; z++) {
					leafPos = new glm::vec3(logPos->x + x, treeLength + yPos + y, logPos->z + z);
					chunk->AddBlock(leafPos->x, leafPos->y, leafPos->z, blockType::OakLeaf);
				}
			}
		}
		//generate the lil' grass blob on top
		for (int x = -1; x < 2; ++x) {
			for (int y = 0; y < 1; y++) {
				for (int z = -1; z < 2; z++) {
					leafPos = new glm::vec3(logPos->x + x, treeLength + yPos + y + 2, logPos->z + z);
					chunk->AddBlock(leafPos->x, leafPos->y, leafPos->z, blockType::OakLeaf);
				}
			}
		}
	}
}

Tree::~Tree() {
	delete logPos;
	delete leafPos;
}
