#pragma once
#include "Chunk.h"

enum entityType {
	Oak_Tree, Birch_Tree, Cactus_Plant
};

class Entity {
private: //section for private constant variables
	const int cactusLength = 3;
	const int treeLength = rand() % 3 + 4;
private: //section for private variables
	int xPos, yPos, zPos;
	Chunk* chunk;
private: //section for private functions
	void spawnOak() const;
	void spawnBirch() const;
	void spawnCactus() const;
	bool ifCorner(int a, int b, int t) const;
public: //section for public functions
	Entity(Chunk* chunk);
	void generateEntity(int x, int y, int z, entityType type);
	bool isNextToEntity(const Chunk& chunk) const;
	~Entity();
};

