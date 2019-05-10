#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "Renderer.h"
#include "Chunk.h"
#include "ChunkMeshGenerator.h"
#include <map>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

class ChunkManager{
private:
	int chunkSize;
	std::unordered_map <glm::vec2, Chunk, std::hash<glm::vec2>> chunks;
	std::unordered_map <glm::vec2, ChunkMesh*, std::hash<glm::vec2>> meshes;
	ChunkMeshGenerator generator;
	Renderer& renderer;
public:
	ChunkManager(Renderer& renderer);
	void addChunk(const Chunk& chunk);
	void removeChunk(int x, int z);
	bool chunkExist(float x, float z);
	Chunk* getChunk(float x, float z);
	Block getBlock(float x, float y, float z);
	BlockType getBlockType(float x, float y, float z);
	BlockType getNeighbourType(float x, float y, float z, Side s);
	void removeBlock(float x, float y, float z);
	void addBlock(float x, float y, float z, BlockType type);
	void displayAllChunks();
};