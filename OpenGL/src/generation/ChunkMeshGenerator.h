#pragma once
#include "VertexArray.h"
#include "Block.h"
#include "Renderable.h"
#include "ChunkMesh.h"
#include "Chunk.h"

class ChunkMeshGenerator {



public:
	ChunkMesh* generateMesh(const Chunk& chunk);
	
};
