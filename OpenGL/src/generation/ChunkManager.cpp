#include "ChunkManager.h"
#include <iostream>

ChunkManager::ChunkManager(Renderer& renderer) : renderer(renderer), chunkSize(0){}

void ChunkManager::addChunk(const Chunk& chunk) {
	glm::vec2 pos(chunk.getXPos(), chunk.getZPos());
	chunks.insert(std::make_pair(pos,chunk));
	meshes.insert(std::make_pair(pos, generator.generateMesh(chunk)));

	if (chunkSize == 0) chunkSize = chunk.getSize();
}

void ChunkManager::removeChunk(int x, int z) {
    glm::vec2 pos(x, z);
	chunks.erase(pos);
	delete meshes[pos];
	meshes.erase(pos);
}

Chunk* ChunkManager::getChunk(float x, float z) {
	x = std::floor(x / (float)chunkSize) * chunkSize;
	z = std::floor(z / (float)chunkSize) * chunkSize;

	if (!chunkExist(x,z)) {
		std::cout << "Chunk with position(" << " x: " << x <<" z: " << z << ") doesn't exist" << std::endl;
		return nullptr;
	}

	return &chunks[glm::vec2(x, z)];
}

Block ChunkManager::getBlock(float x, float y, float z) {
	Chunk* c = getChunk(x, z);

	if (c == nullptr) {
		std::cout << "Block with position(" << " x: " << x << " y: " << y << " z: " << z << ") doesn't exist" << std::endl;
		return Block(0, 0, 0, blockType::Air);
	}
	
	x -= c->getXPos();
	z -= c->getZPos();
	return c->getBlock(x,y,z);
}

blockType ChunkManager::getBlockType(float x, float y, float z) {
	Chunk* c = getChunk(x, z);

	if (c == nullptr) {
		std::cout << "Block with position(" << " x: " << x << " y: " << y << " z: " << z << ") doesn't exist" << std::endl;
		return blockType::Air;
	}

	x -= c->getXPos();
	z -= c->getZPos();

	return c->getBlockType(x, y, z);
}

blockType ChunkManager::getNeighbourType(float x, float y, float z, side s) {
	Chunk* c = getChunk(x, z);

	if (c == nullptr) {
		std::cout << "Block with position(" << " x: " << x << " y: " << y << " z: " << z << ") doesn't exist" << std::endl;
		return blockType::Air;
	}

	x -= c->getXPos();
	z -= c->getZPos();

	if (s == side::Back) return getBlockType(x, y, z - 1);
	if (s == side::Bottom) return getBlockType(x, y - 1, z);
	if (s == side::Front) return getBlockType(x, y, z + 1);
	if (s == side::Left) return getBlockType(x - 1, y, z);
	if (s == side::Right) return getBlockType(x + 1, y, z);
	if (s == side::Top) return getBlockType(x, y + 1, z);
	return blockType::Air;
}

void ChunkManager::removeBlock(float x, float y, float z) {
	Chunk* chunk = getChunk(x, z);
	
	float xChunkSpace = x - chunk->getXPos();
	float zChunkSpace = z - chunk->getZPos();

	chunk->removeBlock(xChunkSpace, y, zChunkSpace);
	ChunkMesh* mesh = meshes[glm::vec2(chunk->getXPos(), chunk->getZPos())];
	delete mesh;
	meshes[glm::vec2(chunk->getXPos(), chunk->getZPos())] = generator.generateMesh(*chunk);
}

void ChunkManager::addBlock(float x, float y, float z, blockType type) {
	Chunk* chunk = getChunk(x, z);
	float xChunkSpace = x - chunk->getXPos();
	float zChunkSpace = z - chunk->getZPos();

	chunk->addBlock(xChunkSpace, y, zChunkSpace, type);
	ChunkMesh* mesh = meshes[glm::vec2(chunk->getXPos(), chunk->getZPos())];
	delete mesh;
	meshes[glm::vec2(chunk->getXPos(), chunk->getZPos())] = generator.generateMesh(*chunk);
}


bool ChunkManager::chunkExist(float x, float z) {
	if (chunks.find(glm::vec2(x, z)) == chunks.end()) return false;
	else return true;
}

void ChunkManager::displayAllChunks() {
    std::unordered_map<glm::vec2,ChunkMesh*>::iterator it;

    for(it = meshes.begin(); it != meshes.end(); it++) {
    	renderer.Draw(it->second);
    }
}
