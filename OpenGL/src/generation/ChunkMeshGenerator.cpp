#include "ChunkMeshGenerator.h"
#include "VertexBufferLayout.h"
#include <vector>
#include <iostream>

const float t = 1.0f / 16.0f;

void ChunkMeshGenerator::addPlane(std::vector<float>* vertexBuffer, Side s, int x, int y, int z, int texX, int texY) const {
	float yMin = (16 - (texY + 1)) * t;
	float yMax = (16 - (texY)) * t;
	float xMin = texX * t;
	float xMax = (texX + 1) * t;

	if (s == Side::Left) {
		float left[] = {
		x - 0.5f,  y + 0.5f,  z + 0.5f, -1.0f, 0.0f, 0.0f,  xMin, yMax,
		x - 0.5f,  y + 0.5f,  z - 0.5f, -1.0f, 0.0f, 0.0f,  xMax, yMax,
		x - 0.5f,  y - 0.5f,  z - 0.5f, -1.0f, 0.0f, 0.0f,  xMax, yMin,
		x - 0.5f,  y - 0.5f,  z - 0.5f, -1.0f, 0.0f, 0.0f,  xMax, yMin,
		x - 0.5f,  y - 0.5f,  z + 0.5f, -1.0f, 0.0f, 0.0f,  xMin, yMin,
		x - 0.5f,  y + 0.5f,  z + 0.5f, -1.0f, 0.0f, 0.0f,  xMin, yMax,
		};
		vertexBuffer->insert(vertexBuffer->end(), &left[0], &left[6 * 8]);
	}

	if (s == Side::Right) {
		float right[] = {
		x + 0.5f,  y + 0.5f,  z + 0.5f, 1.0f, 0.0f, 0.0f, xMin, yMax,
		x + 0.5f,  y + 0.5f,  z - 0.5f, 1.0f, 0.0f, 0.0f, xMax, yMax,
		x + 0.5f,  y - 0.5f,  z - 0.5f, 1.0f, 0.0f, 0.0f, xMax, yMin,
		x + 0.5f,  y - 0.5f,  z - 0.5f, 1.0f, 0.0f, 0.0f, xMax, yMin,
		x + 0.5f,  y - 0.5f,  z + 0.5f, 1.0f, 0.0f, 0.0f, xMin, yMin,
		x + 0.5f,  y + 0.5f,  z + 0.5f, 1.0f, 0.0f, 0.0f, xMin, yMax,
		};
		vertexBuffer->insert(vertexBuffer->end(), &right[0], &right[6 * 8]);
	}

	if (s == Side::Front) {
		float front[] = {
		x - 0.5f, y - 0.5f,  z + 0.5f, 0.0f, 0.0f, 1.0f,  xMin, yMin,
		x + 0.5f, y - 0.5f,  z + 0.5f, 0.0f, 0.0f, 1.0f,  xMax, yMin,
		x + 0.5f, y + 0.5f,  z + 0.5f, 0.0f, 0.0f, 1.0f,  xMax, yMax,
		x + 0.5f, y + 0.5f,  z + 0.5f, 0.0f, 0.0f, 1.0f,  xMax, yMax,
		x - 0.5f, y + 0.5f,  z + 0.5f, 0.0f, 0.0f, 1.0f,  xMin, yMax,
		x - 0.5f, y - 0.5f,  z + 0.5f, 0.0f, 0.0f, 1.0f,  xMin, yMin,
		};
		vertexBuffer->insert(vertexBuffer->end(), &front[0], &front[6 * 8]);
	}

	if (s == Side::Back) {
		float back[] = {
		x - 0.5f, y - 0.5f, z - 0.5f, 0.0f, 0.0f, -1.0f,  xMin, yMin,
		x + 0.5f, y - 0.5f, z - 0.5f, 0.0f, 0.0f, -1.0f,  xMax, yMin,
		x + 0.5f, y + 0.5f, z - 0.5f, 0.0f, 0.0f, -1.0f,  xMax, yMax,
		x + 0.5f, y + 0.5f, z - 0.5f, 0.0f, 0.0f, -1.0f,  xMax, yMax,
		x - 0.5f, y + 0.5f, z - 0.5f, 0.0f, 0.0f, -1.0f,  xMin, yMax,
		x - 0.5f, y - 0.5f, z - 0.5f, 0.0f, 0.0f, -1.0f,  xMin, yMin,
		};
		vertexBuffer->insert(vertexBuffer->end(), &back[0], &back[6 * 8]);
	}

	if (s == Side::Top) {
		float top[] = {
		x - 0.5f,  y + 0.5f, z - 0.5f, 0.0f, 1.0f, 0.0f, xMin, yMax,
		x + 0.5f,  y + 0.5f, z - 0.5f, 0.0f, 1.0f, 0.0f, xMax, yMax,
		x + 0.5f,  y + 0.5f, z + 0.5f, 0.0f, 1.0f, 0.0f, xMax, yMin,
		x + 0.5f,  y + 0.5f, z + 0.5f, 0.0f, 1.0f, 0.0f, xMax, yMin,
		x - 0.5f,  y + 0.5f, z + 0.5f, 0.0f, 1.0f, 0.0f, xMin, yMin,
		x - 0.5f,  y + 0.5f, z - 0.5f, 0.0f, 1.0f, 0.0f, xMin, yMax
		};
		vertexBuffer->insert(vertexBuffer->end(), &top[0], &top[6 * 8]);
	}

	if (s == Side::Bottom) {
		float bottom[] = {
		x - 0.5f, y - 0.5f,  z - 0.5f, 0.0f, -1.0f, 0.0f,  xMin, yMax,
		x + 0.5f, y - 0.5f,  z - 0.5f, 0.0f, -1.0f, 0.0f,  xMax, yMax,
		x + 0.5f, y - 0.5f,  z + 0.5f, 0.0f, -1.0f, 0.0f,  xMax, yMin,
		x + 0.5f, y - 0.5f,  z + 0.5f, 0.0f, -1.0f, 0.0f,  xMax, yMin,
		x - 0.5f, y - 0.5f,  z + 0.5f, 0.0f, -1.0f, 0.0f,  xMin, yMin,
		x - 0.5f, y - 0.5f,  z - 0.5f, 0.0f, -1.0f, 0.0f,  xMin, yMax,
		};
		vertexBuffer->insert(vertexBuffer->end(), &bottom[0], &bottom[6 * 8]);
	}

}

void ChunkMeshGenerator::addBlock(std::vector<float>* vertexBuffer, Block b) const {
	for (int i = 0; i < 6; i++) {
		BlockPlane bp = b.planes[(Side)i];
		addPlane(vertexBuffer, bp.side, b.getXPos(), b.getYPos(), b.getZPos(), bp.xTex, bp.yTex);
	}
}

ChunkMeshGenerator::ChunkMeshGenerator() {
	layout = new VertexBufferLayout;
	layout->push<float>(3);
	layout->push<float>(3);
	layout->push<float>(2);
}

ChunkMesh* ChunkMeshGenerator::generateMesh(const Chunk& chunk) const {
	ChunkMesh* mesh = new ChunkMesh;

	mesh->va = new VertexArray;
	mesh->buffer = new std::vector<float>;

	int height = chunk.getHeight();
	int size = chunk.getSize();

	for (int x = 0; x < size; x++) {
		for (int y = 0; y < height; y++) {
			for (int z = 0; z < size; z++) {
				BlockType b = chunk.getBlockType(x, y, z);
				if (b != BlockType::Air) {
					for (int i = 0; i < 6; i++) {
						BlockType temp = chunk.getNeighbourType(x, y, z, (Side)i);
						if (temp == BlockType::Air) {
							Block bl = chunk.getBlock(x, y, z);
							addPlane(mesh->buffer, (Side)i, x + chunk.getXPos(), y, z + chunk.getZPos(), 
															bl.planes[(Side)i].xTex, bl.planes[(Side)i].yTex);
						}
					}
				}
			}
		}
	}

	VertexBuffer* vb = new VertexBuffer(&((*mesh->buffer)[0]), mesh->buffer->size() * sizeof(float));

	mesh->va->addBuffer(*vb, *layout);
	return mesh;
}



