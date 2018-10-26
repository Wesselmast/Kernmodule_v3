#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <vector>

class ChunkMesh {
public: //section for public variables
	std::vector<float>* buffer;
	VertexArray* va;
	VertexBufferLayout* layout;
public: //section for public functions
	ChunkMesh(){}
	~ChunkMesh() { delete va; delete layout; delete buffer; }
};