#pragma once
#include "glm/gtc/matrix_transform.hpp"
#include "Chunk.h"

class Plant
{
private:
	int xPos, yPos, zPos;
	int cactusLength = 3;
public:
	Plant();
	void generatePlant(glm::vec3* grassPos, Chunk* chunk, blockType type);
	~Plant();
};

