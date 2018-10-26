#pragma once
#include "Block.h"
#include <vector>

class Chunk {
private: //section for private variables
	int size, height;
	int xPos, yPos, zPos;
	std::vector<std::vector<std::vector<char>>> blocks;
public: //section for public functions
	Chunk();
	Chunk(int size,int height, int xPos, int yPos, int zPos);
	void addBlock(int x, int y, int z, blockType t);
	void removeBlock(int x, int y, int z);
	int getSize() const { return size; }
	int getHeight() const { return height; }
	int getXPos() const { return xPos; }
	int getZPos() const { return zPos; }
	Block getBlock(int x, int y, int z) const;
	Block getNeighbour(int x, int y, int z, side s) const;
	blockType getBlockType(int x, int y, int z) const;
	blockType getNeighbourType(int x, int y, int z, side s) const;
	~Chunk();
};
