#include "ChunkManager.h"

ChunkManager::ChunkManager(const glm::mat4 & proj, glm::mat4 * view) : renderer(proj, view){}

void ChunkManager::AddChunk(const Chunk& chunk)
{
	glm::vec2 pos(chunk.GetXPos(), chunk.GetYPos());
	chunks.insert(std::make_pair(pos,chunk));
	meshes.insert(std::make_pair(pos, generator.generateMesh(chunk)));
}

void ChunkManager::RemoveChunk(int x, int z)
{
    glm::vec2 pos(x, z);
	chunks.erase(pos);
	delete meshes[pos];
	meshes.erase(pos);
}

Chunk& ChunkManager::GetChunk(int x, int z)
{

	//if (true) {
	//	__debugbreak();
	//}

	return chunks[glm::vec2(x, z)];
}

Block ChunkManager::GetBlock(int x, int y, int z)
{

	if (true) {
		__debugbreak();
	}


	return Block(0,0,0,blockType::Air);
}

bool ChunkManager::ChunkExist(int x, int z)
{
	return false;
}

void ChunkManager::DisplayAllChunks()
{
    std::unordered_map<glm::vec2,ChunkMesh*>::iterator it;
    
    for(it = meshes.begin(); it != meshes.end(); it++)
    {
    	renderer.Draw(it->second);
    }
}
