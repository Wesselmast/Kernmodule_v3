#include "ChunkManager.h"
#include <iostream>

ChunkManager::ChunkManager(Renderer& renderer) : renderer(renderer), ChunkSize(0){}

void ChunkManager::AddChunk(const Chunk& chunk)
{
	glm::vec2 pos(chunk.GetXPos(), chunk.GetYPos());
	chunks.insert(std::make_pair(pos,chunk));
	meshes.insert(std::make_pair(pos, generator.generateMesh(chunk)));

	if (ChunkSize == 0)
		ChunkSize = chunk.GetSize();
}

void ChunkManager::RemoveChunk(int x, int z)
{
    glm::vec2 pos(x, z);
	chunks.erase(pos);
	delete meshes[pos];
	meshes.erase(pos);
}

Chunk* ChunkManager::GetChunk(float x, float z)
{
	x = std::floor(x / (float)ChunkSize) * ChunkSize;
	z = std::floor(z / (float)ChunkSize) * ChunkSize;

	if (!ChunkExist(x,z)) {
		std::cout << "Chunk with position(" << " x: " << x <<" z: " << z << ") doesn't exist" << std::endl;
		return nullptr;
	}


	return &chunks[glm::vec2(x, z)];
}

Block ChunkManager::GetBlock(float x, float y, float z)
{
	Chunk* c = GetChunk(x, z);

	if (c == nullptr) {
		std::cout << "Block with position(" << " x: " << x << " y: " << y << " z: " << z << ") doesn't exist" << std::endl;
		return Block(0, 0, 0, blockType::Air);
	}	
	
	x -= c->GetXPos();

	//if (x < 0)
	//	x = x - ChunkSize;
	
	//std::cout << x <<  " " << c->GetXPos() <<  "   ";

	z -= c->GetYPos();

	//if (z >= ChunkSize)
	//	z = z - ChunkSize;
	
	return c->GetBlock(x,y,z);
}

bool ChunkManager::ChunkExist(float x, float z)
{
	if (chunks.find(glm::vec2(x, z)) == chunks.end())
		return false;
	else
		return true;
}

void ChunkManager::DisplayAllChunks()
{
    std::unordered_map<glm::vec2,ChunkMesh*>::iterator it;
    
    for(it = meshes.begin(); it != meshes.end(); it++)
    {
    	renderer.Draw(it->second);
    }
}
