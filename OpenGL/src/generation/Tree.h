#pragma once
#include "glm/gtc/matrix_transform.hpp"
#include "Chunk.h"


class Tree
{
private:
	int xPos, yPos, zPos;
	glm::vec3* logPos;
	glm::vec3* leafPos;
public:
	Tree();
	void generateTree(glm::vec3* grassPos, Chunk* chunk);
	~Tree();
};

