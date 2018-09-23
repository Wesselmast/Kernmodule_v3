#pragma once
#include "VertexArray.h"
#include "Block.h"
#include "Renderable.h"
#include "ChunkMesh.h"

class ChunkMeshGenerator {



public:
	ChunkMesh* generateMesh(int x, int y, int z);
	
};
