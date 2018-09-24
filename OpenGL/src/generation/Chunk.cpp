#include "Chunk.h"

Chunk::Chunk(int size, int xPos, int yPos, int zPos) :
	size(size), xPos(xPos), yPos(yPos), zPos(zPos)
{
	for (int x = 0; x < size; x++)
	{
		std::vector<std::vector<Block>> temp;

		for (int y = 0; y < size; y++)
		{

			std::vector<Block> temp2;

			for (int z = 0; z < size; z++)
			{
				temp2.push_back(Block(x + xPos,y + yPos,z + zPos,blockType::Air));
			}

			temp.push_back(temp2);
		}

		blocks.push_back(temp);
	}
}

void Chunk::AddBlock(int x, int y, int z, blockType t)
{
	blocks[x][y][z] = Block(x + xPos, y + yPos, z + zPos, t);
}
