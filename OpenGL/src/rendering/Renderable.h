#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"

class Renderable
{


public:
	Renderable(const VertexArray& va, const IndexBuffer& ib) : va(va), ib(ib) {}
	VertexArray va;
	IndexBuffer ib;
};