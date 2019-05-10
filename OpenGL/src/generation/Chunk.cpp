#include "Chunk.h"

Chunk::Chunk() : size(0), height(0), xPos(0), yPos(0), zPos(0) {
}

Chunk::Chunk(int size, int height, int xPos, int yPos, int zPos) :
	size(size), height(height), xPos(xPos), yPos(yPos), zPos(zPos), 
	blocks(size, std::vector<std::vector<char>>(height, std::vector<char>(size, (char)BlockType::Air))) {
}

void Chunk::addBlock(int x, int y, int z, BlockType t) {
	if (size == 0 || height == 0) return;
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (z < 0) z = 0;
	if (x > size - 1) x = size - 1;
	if (y > height - 1) y = height - 1;
	if (z > size - 1) z = size - 1;
	blocks[x][y][z] = t;
}

void Chunk::removeBlock(int x, int y, int z) {
	blocks[x][y][z] = (char)BlockType::Air;
}

Block Chunk::getBlock(int x, int y, int z) const {
	if (size == 0 || height == 0) return Block(0, 0, 0, BlockType::Air);
	if (x < 0) return Block(0, 0, 0, BlockType::Air);
	if (y < 0) return Block(0, 0, 0, BlockType::Air);
	if (z < 0) return Block(0, 0, 0, BlockType::Air);
	if (x > size - 1) return Block(0, 0, 0, BlockType::Air);
	if (y > height - 1) return Block(0, 0, 0, BlockType::Air);
	if (z > size - 1) return Block(0, 0, 0, BlockType::Air);
	return Block(x, y, z, (BlockType)blocks[x][y][z]);
}

Block Chunk::getNeighbour(int x, int y, int z, Side s) const {
	if (s == Side::Back) return getBlock(x, y, z - 1);
	if (s == Side::Bottom) return getBlock(x, y - 1, z);
	if (s == Side::Front) return getBlock(x, y, z + 1);
	if (s == Side::Left) return getBlock(x - 1, y, z);
	if (s == Side::Right) return getBlock(x + 1, y, z);
	if (s == Side::Top) return getBlock(x, y + 1, z);
	return Block(0, 0, 0, BlockType::Air);
}

BlockType Chunk::getBlockType(int x, int y, int z) const {
	if (size == 0 || height == 0) return BlockType::Air;
	if (x < 0) return BlockType::Air;
	if (y < 0) return BlockType::Air;
	if (z < 0) return BlockType::Air;
	if (x > size - 1) return BlockType::Air;
	if (y > height - 1) return BlockType::Air;
	if (z > size - 1) return BlockType::Air;
	return (BlockType)blocks[x][y][z];
}

BlockType Chunk::getNeighbourType(int x, int y, int z, Side s) const {
	if (s == Side::Back) return getBlockType(x, y, z - 1);
	if (s == Side::Bottom) return getBlockType(x, y - 1, z);
	if (s == Side::Front) return getBlockType(x, y, z + 1);
	if (s == Side::Left) return getBlockType(x - 1, y, z);
	if (s == Side::Right) return getBlockType(x + 1, y, z);
	if (s == Side::Top) return getBlockType(x, y + 1, z);
	return BlockType::Air;
}

Chunk::~Chunk() {
}

