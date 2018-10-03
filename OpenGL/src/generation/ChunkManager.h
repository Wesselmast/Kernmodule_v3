#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "Renderer.h"
#include "Chunk.h"
#include "ChunkMeshGenerator.h"
#include <map>
#include <glm\glm.hpp>
#include <glm/gtx/hash.hpp>



class ChunkManager{

private:
	int ChunkSize;
	std::unordered_map <glm::vec2, Chunk, std::hash<glm::vec2>> chunks;
	std::unordered_map <glm::vec2, ChunkMesh*, std::hash<glm::vec2>> meshes;

	ChunkMeshGenerator generator;

	Renderer renderer;

public:

	//===== ALL COORDINATES ARE WORLD SPACE ======
	ChunkManager(const glm::mat4 & proj, glm::mat4 * view);

	void AddChunk(const Chunk& chunk);
	void RemoveChunk(int x, int z);

	Chunk& GetChunk(int x, int z);
	Block GetBlock(int x, int y, int z);
	bool ChunkExist(int x, int z);


	void DisplayAllChunks();

};