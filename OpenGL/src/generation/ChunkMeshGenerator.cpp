#include "ChunkMeshGenerator.h"
#include "VertexBufferLayout.h"
#include <vector>
#include <iostream>




const float t = 1.0f / 16.0f;

void Addplane(std::vector<float>* vertexBuffer, side s, int x, int y, int z, int texX, int texY) {

	float ux = x;
	float uy = y;
	float uz = z;

	float yMin = (16 - (texY + 1)) * t;
	float yMax = (16 - (texY)) * t;
	float xMin = texX * t;
	float xMax = (texX + 1) * t;
											 																					
	if (s == side::Left) {
		float left[] = {							 
		//left							    	 
		ux - 0.5f,  uy + 0.5f,  uz + 0.5f,  xMin, yMax,
		ux - 0.5f,  uy + 0.5f,  uz - 0.5f,  xMax, yMax,
		ux - 0.5f,  uy - 0.5f,  uz - 0.5f,  xMax, yMin,
		ux - 0.5f,  uy - 0.5f,  uz - 0.5f,  xMax, yMin,
		ux - 0.5f,  uy - 0.5f,  uz + 0.5f,  xMin, yMin,
		ux - 0.5f,  uy + 0.5f,  uz + 0.5f,  xMin, yMax,

	};
		vertexBuffer->insert(vertexBuffer->end(), &left[0], &left[6 * 5]);
	}

	if (s == side::Right) {
		float right[] = {
		//right							    
		ux + 0.5f,  uy + 0.5f,  uz + 0.5f,  xMin, yMax,
		ux + 0.5f,  uy + 0.5f,  uz - 0.5f,  xMax, yMax,
		ux + 0.5f,  uy - 0.5f,  uz - 0.5f,  xMax, yMin,
		ux + 0.5f,  uy - 0.5f,  uz - 0.5f,  xMax, yMin,
		ux + 0.5f,  uy - 0.5f,  uz + 0.5f,  xMin, yMin,
		ux + 0.5f,  uy + 0.5f,  uz + 0.5f,  xMin, yMax,
	};	
		vertexBuffer->insert(vertexBuffer->end(), &right[0], &right[6 * 5]);
	}

	if (s == side::Front) {
		float front[] = {							 
		//front									 
		ux - 0.5f, uy - 0.5f,  uz + 0.5f,   xMin, yMin,
		ux + 0.5f, uy - 0.5f,  uz + 0.5f,   xMax, yMin,
		ux + 0.5f, uy + 0.5f,  uz + 0.5f,   xMax, yMax,
		ux + 0.5f, uy + 0.5f,  uz + 0.5f,   xMax, yMax,
		ux - 0.5f, uy + 0.5f,  uz + 0.5f,   xMin, yMax,
		ux - 0.5f, uy - 0.5f,  uz + 0.5f,   xMin, yMin,
	};	
		vertexBuffer->insert(vertexBuffer->end(), &front[0], &front[6 * 5]);
	}

	if (s == side::Back) {
		float back[] = {							 
		//back									 
		ux - 0.5f, uy - 0.5f, uz - 0.5f,   xMin, yMin,
		ux + 0.5f, uy - 0.5f, uz - 0.5f,   xMax, yMin,
		ux + 0.5f, uy + 0.5f, uz - 0.5f,   xMax, yMax,
		ux + 0.5f, uy + 0.5f, uz - 0.5f,   xMax, yMax,
		ux - 0.5f, uy + 0.5f, uz - 0.5f,   xMin, yMax,
		ux - 0.5f, uy - 0.5f, uz - 0.5f,   xMin, yMin,
	};	
		vertexBuffer->insert(vertexBuffer->end(), &back[0], &back[6 * 5]);
	}

	if (s == side::Top) {
		float top[] = {								 
		//top							    	 
		ux - 0.5f,  uy + 0.5f,  uz - 0.5f,  xMin, yMax,
		ux + 0.5f,   uy + 0.5f, uz - 0.5f,  xMax, yMax,
		ux + 0.5f,   uy + 0.5f, uz + 0.5f,  xMax, yMin,
		ux + 0.5f,   uy + 0.5f, uz + 0.5f,  xMax, yMin,
		ux - 0.5f,  uy + 0.5f,  uz + 0.5f,  xMin, yMin,
		ux - 0.5f,  uy + 0.5f,  uz - 0.5f,  xMin, yMax
	};		
		vertexBuffer->insert(vertexBuffer->end(), &top[0], &top[6 * 5]);
	}

	if (s == side::Bottom) {
		float bottom[] = {							 
		//bottom						    	 
		ux - 0.5f, uy - 0.5f,  uz - 0.5f,   xMin, yMax,
		ux + 0.5f, uy - 0.5f,  uz - 0.5f,   xMax, yMax,
		ux + 0.5f, uy - 0.5f,  uz + 0.5f,   xMax, yMin,
		ux + 0.5f, uy - 0.5f,  uz + 0.5f,   xMax, yMin,
		ux - 0.5f, uy - 0.5f,  uz + 0.5f,   xMin, yMin,
		ux - 0.5f, uy - 0.5f,  uz - 0.5f,   xMin, yMax,
	};		
		vertexBuffer->insert(vertexBuffer->end(), &bottom[0], &bottom[6 * 5]);
	}

}

void AddBlock(std::vector<float>* vertexBuffer, Block b) {
	for (int i = 0; i < 6; i++) {
		BlockPlane bp = b.Planes[(side)i];
		Addplane(vertexBuffer, bp.s, b.getXPos(), b.getYPos(), b.getZPos(), bp.xTex, bp.yTex);
	}
}

ChunkMesh* ChunkMeshGenerator::generateMesh(const Chunk& chunk)
{

	ChunkMesh* mesh = new ChunkMesh;

	mesh->va = new VertexArray;

	VertexBufferLayout* layout = new VertexBufferLayout;
	std::vector<float>* vec = new std::vector<float>;


	for (int x = 0; x < chunk.GetSize(); x++) {
		for (int y = 0; y < chunk.GetSize(); y++) {
			for (int z = 0; z < chunk.GetSize(); z++) {
				Block b = chunk.GetBlock(x,y,z);
					if (b.getType() != blockType::Air) {

						for (int i = 0; i < 6; i++) {
							Block temp = chunk.GetNeighbour(x, y, z, (side)i);
							if ((temp.getType() == blockType::Air) || ((temp.getXPos() == b.getXPos()) && (temp.getYPos() == b.getYPos()) && (temp.getZPos() == b.getZPos()))) {
								Addplane(vec, (side)i, x, y, z, b.Planes[(side)i].xTex, b.Planes[(side)i].yTex);
							}
						}
					
					}
			}
		}
	}

	mesh->buffer = vec;

	std::vector<float>* v = mesh->buffer;

	if (v->size() > 0) {
		VertexBuffer* vb = new VertexBuffer(&((*v)[0]), v->size() * sizeof(float));

		layout->Push<float>(3);
		layout->Push<float>(2);
		mesh->va->AddBuffer(*vb, *layout);
	}

	return mesh;
}



