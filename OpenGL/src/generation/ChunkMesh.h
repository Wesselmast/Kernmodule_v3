#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <vector>

class ChunkMesh {

private:


public:
	ChunkMesh(){}
	~ChunkMesh() { delete vb; delete va; delete layout; }

	std::vector<float>* buffer;
	VertexBuffer* vb;
	VertexArray* va;
	VertexBufferLayout* layout;

};