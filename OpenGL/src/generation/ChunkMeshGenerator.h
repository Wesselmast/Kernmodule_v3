#pragma once
#include "VertexArray.h"
#include "Block.h"
#include "ChunkMesh.h"
#include "Chunk.h"


class ChunkMeshGenerator {
private: //section for private variables
	VertexBufferLayout* layout;
private: //section for private functions
	void addPlane(std::vector<float>* vertexBuffer, side s, int x, int y, int z, int texX, int texY) const;
	void addBlock(std::vector<float>* vertexBuffer, Block b) const;
public: //section for public functions
	ChunkMeshGenerator();
	ChunkMesh* generateMesh(const Chunk& chunk) const;
};
