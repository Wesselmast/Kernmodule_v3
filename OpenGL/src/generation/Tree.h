#pragma once
#include "glm/gtc/matrix_transform.hpp"
#include "Chunk.h"

enum treeType {
	Spruce, Oak, Birch
};

class Tree {
private:
	int xPos, yPos, zPos;
	int treeLength;
	glm::vec3* logPos;
	glm::vec3* leafPos;
private:
	void spawnOak(Chunk* chunk);
	void spawnSpruce(Chunk* chunk);
	void spawnBirch(Chunk* chunk);
	bool ifCorner(int a, int b, int t);
public:
	Tree();
	void generateTree(glm::vec3* topLayer, Chunk* chunk, treeType type);
	~Tree();
};

