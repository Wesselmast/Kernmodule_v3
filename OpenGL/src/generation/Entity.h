#pragma once
#include "glm/gtc/matrix_transform.hpp"
#include "Chunk.h"

enum entityType {
	Oak_Tree, Birch_Tree, Cactus_Plant
};


class Entity {
private: //section for constants
	const int cactusLength = 3;
private: //section for private variables
	int xPos, yPos, zPos;
private: //section for private functions
	void spawnOak(Chunk* chunk);
	void spawnBirch(Chunk* chunk);
	void spawnCactus(Chunk* chunk);
	bool ifCorner(int a, int b, int t);
public: //section for public functions
	Entity();
	void generateEntity(int x, int y, int z, Chunk* chunk, entityType type);
	~Entity();
};

