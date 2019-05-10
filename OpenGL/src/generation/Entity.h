#pragma once
#include "Chunk.h"

enum EntityType {
	Oak_Tree, Birch_Tree, Cactus_Plant
};

class Entity {
private:
	const int cactusLength = 3;
	const int treeLength = rand() % 3 + 4;
private:
	int xPos, yPos, zPos;
	Chunk* chunk;
private:
	void spawnOak() const;
	void spawnBirch() const;
	void spawnCactus() const;
	bool ifCorner(int a, int b, int t) const;
public:
	Entity(Chunk* chunk);
	void generateEntity(int x, int y, int z, EntityType type);
	bool isNextToEntity(const Chunk& chunk) const;
	~Entity();
};

