#pragma once
#include "VertexArray.h"
#include "Block.h"
#include "ChunkMesh.h"
#include "Chunk.h"

class ChunkMeshGenerator {
private:
	VertexBufferLayout* layout;
private:
	void addPlane(std::vector<float>* vertexBuffer, Side s, int x, int y, int z, int texX, int texY) const;
	void addBlock(std::vector<float>* vertexBuffer, Block b) const;
public:
	ChunkMeshGenerator();
	ChunkMesh* generateMesh(const Chunk& chunk) const;
};
