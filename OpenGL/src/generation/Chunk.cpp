#include "Chunk.h"

Chunk::Chunk(int size, int xPos, int yPos, int zPos) :
	size(size), xPos(xPos), yPos(yPos), zPos(zPos)
{

	blocks.reserve(size);
	
	for (int x = 0; x < size; x++)
	{
		std::vector<std::vector<Block>> temp;
		temp.reserve(size);

		for (int y = 0; y < size; y++)
		{

			std::vector<Block> temp2;
			temp2.reserve(size);

			for (int z = 0; z < size; z++)
			{
				temp2.emplace_back(Block(x + xPos,y + yPos,z + zPos,blockType::Air));
			}

			temp.emplace_back(temp2);
		}

		blocks.emplace_back(temp);
	}
	
}

void Chunk::AddBlock(int x, int y, int z, blockType t)
{
	if (size == 0)
		return;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (z < 0)
		z = 0;
	
	if (x > size - 1)
		x = size - 1;
	if (y > size - 1)
		y = size - 1;
	if (z > size - 1)
		z = size - 1;

	blocks[x][y][z] = Block(x + xPos, y + yPos, z + zPos, t);
}

Block Chunk::GetBlock(int x, int y, int z) const
{
	if (size == 0)
		return Block(0,0,0,blockType::Air);

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (z < 0)
		z = 0;

	if (x > size - 1)
		x = size - 1;
	if (y > size - 1)
		y = size - 1;
	if (z > size - 1)
		z = size - 1;



	return blocks[x][y][z];
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
