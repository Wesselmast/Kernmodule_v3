#include "Chunk.h"

Chunk::Chunk(int size, int height, int xPos, int yPos, int zPos) :
	size(size),height(height), xPos(xPos), yPos(yPos), zPos(zPos), blocks(size, std::vector<std::vector<blockType>>(height, std::vector<blockType>(size,blockType::Air)))
{	
}

void Chunk::AddBlock(int x, int y, int z, blockType t)
{
	if (size == 0 || height == 0)
		return;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (z < 0)
		z = 0;
	
	if (x > size - 1)
		x = size - 1;
	if (y > height - 1)
		y = height - 1;
	if (z > size - 1)
		z = size - 1;

	blocks[x][y][z] = t;
}

Block Chunk::GetBlock(int x, int y, int z) const
{
	if (size == 0 || height == 0)
		return Block(0,0,0,blockType::Air);

	if (x < 0)
		return Block(0, 0, 0, blockType::Air);
	if (y < 0)
		return Block(0, 0, 0, blockType::Air);
	if (z < 0)
		return Block(0, 0, 0, blockType::Air);
	if (x > size - 1)
		return Block(0, 0, 0, blockType::Air);
	if (y > height - 1)
		return Block(0, 0, 0, blockType::Air);
	if (z > size - 1)
		return Block(0, 0, 0, blockType::Air);


	return Block(x,y,z,blocks[x][y][z]);
}

Block Chunk::GetNeighbour(int x, int y, int z, side s) const
{
	if (s == side::Back) {
		return GetBlock(x, y, z - 1);
	}
	if (s == side::Bottom) {
		return GetBlock(x, y - 1, z);
	}
	if (s == side::Front) {
		return GetBlock(x, y, z + 1);
	}
	if (s == side::Left) {
		return GetBlock(x - 1, y, z);
	}
	if (s == side::Right) {
		return GetBlock(x + 1, y, z);
	}
	if (s == side::Top) {
		return GetBlock(x, y + 1, z);
	}
	return Block(0, 0, 0, blockType::Air);
}
