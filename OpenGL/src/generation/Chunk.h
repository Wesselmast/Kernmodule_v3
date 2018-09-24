#pragma once
#include "Block.h"
#include <vector>
#include <array>

class Chunk {

private:
	int size;
	int xPos, yPos, zPos;
	std::vector<std::vector<std::vector<Block>>> blocks;

public:
	Chunk(int size, int xPos, int yPos, int zPos);
	void AddBlock(int x, int y, int z, blockType t);
	int GetSize() const { return size; }
	Block GetBlock(int x, int y, int z) const;
	Block GetNeighbour(int x, int y, int z, side s) const;
};
