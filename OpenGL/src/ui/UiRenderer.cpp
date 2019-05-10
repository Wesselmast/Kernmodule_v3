#include "UiRenderer.h"

const float t = 1.0f / 16.0f;

float quad[] = {
	 0,	0,	0, 0,
	 0,	1,	1, 0,
	 1,	1,	1, 1,
	 1,	1,	1, 1,
	 1,	0,	0, 1,
	 0,	0,	0, 0
};

void addPlane(std::vector<float>& vertexBuffer, Side s, int texX, int texY) {
	float yMin = (16 - (texY + 1)) * t;
	float yMax = (16 - (texY)) * t;
	float xMin = texX * t;
	float xMax = (texX + 1) * t;

	if (s == Side::Left) {
		float left[] = {
			//left							    	 
			 -0.5f,   0.5f,  0.5f, -1.0f, 0.0f, 0.0f,  xMin, yMax,
			 -0.5f,   0.5f,  -0.5f, -1.0f, 0.0f, 0.0f,  xMax, yMax,
			 -0.5f,   -0.5f,  -0.5f, -1.0f, 0.0f, 0.0f,  xMax, yMin,
			 -0.5f,   -0.5f,  -0.5f, -1.0f, 0.0f, 0.0f,  xMax, yMin,
			 -0.5f,   -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,  xMin, yMin,
			 -0.5f,   0.5f,  0.5f, -1.0f, 0.0f, 0.0f,  xMin, yMax,

		};
		vertexBuffer.insert(vertexBuffer.end(), &left[0], &left[6 * 8]);
	}

	if (s == Side::Right) {
		float right[] = {
			//right							    
			 0.5f,   0.5f,   +0.5f, 1.0f, 0.0f, 0.0f, xMin, yMax,
			 0.5f,   0.5f,   -0.5f, 1.0f, 0.0f, 0.0f, xMax, yMax,
			 0.5f,   -0.5f,   -0.5f, 1.0f, 0.0f, 0.0f, xMax, yMin,
			 0.5f,   -0.5f,   -0.5f, 1.0f, 0.0f, 0.0f, xMax, yMin,
			 0.5f,   -0.5f,   +0.5f, 1.0f, 0.0f, 0.0f, xMin, yMin,
			 0.5f,   +0.5f,   +0.5f, 1.0f, 0.0f, 0.0f, xMin, yMax,
		};
		vertexBuffer.insert(vertexBuffer.end(), &right[0], &right[6 * 8]);
	}

	if (s == Side::Front) {
		float front[] = {
			//front									 
			 -0.5f,  -0.5f,   +0.5f, 0.0f, 0.0f, 1.0f,  xMin, yMin,
			 +0.5f,  -0.5f,   +0.5f, 0.0f, 0.0f, 1.0f,  xMax, yMin,
			 +0.5f,  +0.5f,   +0.5f, 0.0f, 0.0f, 1.0f,  xMax, yMax,
			 +0.5f,  +0.5f,   +0.5f, 0.0f, 0.0f, 1.0f,  xMax, yMax,
			 -0.5f,  +0.5f,   +0.5f, 0.0f, 0.0f, 1.0f,  xMin, yMax,
			 -0.5f,  -0.5f,   +0.5f, 0.0f, 0.0f, 1.0f,  xMin, yMin,
		};
		vertexBuffer.insert(vertexBuffer.end(), &front[0], &front[6 * 8]);
	}

	if (s == Side::Back) {
		float back[] = {
			//back									 
			 -0.5f,  -0.5f,  -0.5f, 0.0f, 0.0f, -1.0f,  xMin, yMin,
			 +0.5f,  -0.5f,  -0.5f, 0.0f, 0.0f, -1.0f,  xMax, yMin,
			 +0.5f,  +0.5f,  -0.5f, 0.0f, 0.0f, -1.0f,  xMax, yMax,
			 +0.5f,  +0.5f,  -0.5f, 0.0f, 0.0f, -1.0f,  xMax, yMax,
			 -0.5f,  +0.5f,  -0.5f, 0.0f, 0.0f, -1.0f,  xMin, yMax,
			 -0.5f,  -0.5f,  -0.5f, 0.0f, 0.0f, -1.0f,  xMin, yMin,
		};
		vertexBuffer.insert(vertexBuffer.end(), &back[0], &back[6 * 8]);
	}

	if (s == Side::Top) {
		float top[] = {
			//top							    	 
			 -0.5f,   +0.5f,   -0.5f, 0.0f, 1.0f, 0.0f, xMin, yMax,
			 +0.5f,   +0.5f,   -0.5f, 0.0f, 1.0f, 0.0f, xMax, yMax,
			 +0.5f,   +0.5f,   +0.5f, 0.0f, 1.0f, 0.0f, xMax, yMin,
			 +0.5f,   +0.5f,   +0.5f, 0.0f, 1.0f, 0.0f, xMax, yMin,
			 -0.5f,   +0.5f,   +0.5f, 0.0f, 1.0f, 0.0f, xMin, yMin,
			 -0.5f,   +0.5f,   -0.5f, 0.0f, 1.0f, 0.0f, xMin, yMax
		};
		vertexBuffer.insert(vertexBuffer.end(), &top[0], &top[6 * 8]);
	}

	if (s == Side::Bottom) {
		float bottom[] = {
			//bottom						    	 
			 -0.5f,  -0.5f,   -0.5f, 0.0f, -1.0f, 0.0f,  xMin, yMax,
			 +0.5f,  -0.5f,   -0.5f, 0.0f, -1.0f, 0.0f,  xMax, yMax,
			 +0.5f,  -0.5f,   +0.5f, 0.0f, -1.0f, 0.0f,  xMax, yMin,
			 +0.5f,  -0.5f,   +0.5f, 0.0f, -1.0f, 0.0f,  xMax, yMin,
			 -0.5f,  -0.5f,   +0.5f, 0.0f, -1.0f, 0.0f,  xMin, yMin,
			 -0.5f,  -0.5f,   -0.5f, 0.0f, -1.0f, 0.0f,  xMin, yMax,
		};
		vertexBuffer.insert(vertexBuffer.end(), &bottom[0], &bottom[6 * 8]);
	}

}
void createCube(std::vector<float>& vertexBuffer, Block block) {
	for (int i = 0; i < 6; i++) {
		addPlane(vertexBuffer, (Side)i, block.planes[(Side)i].xTex, block.planes[(Side)i].yTex);
	}
}

UiRenderer::UiRenderer(Renderer & renderer) : renderer(renderer), vb(quad, 6 * 4 * sizeof(float)), Ui("res/shaders/Ui.shader"), terrain("res/textures/CANDEMAN.png"), cubeShader("res/shaders/CubeUi.shader") {
	for (size_t i = 0; i < 9; i++) {
		iconMeshes.push_back(new ChunkMesh());
		iconMeshes[i]->buffer = new std::vector<float>();
		iconMeshes[i]->va = new VertexArray();
	}

	lay.push<float>(2);
	lay.push<float>(2);
	quadMesh.addBuffer(vb, lay);

	cubeLayout.push<float>(3);
	cubeLayout.push<float>(3);
	cubeLayout.push<float>(2);

	for (size_t i = 0; i < 9; i++) {
		createCube(*iconMeshes[i]->buffer, Block(0, 0, 0, (BlockType)i));
		VertexBuffer* temp = new VertexBuffer(&((*iconMeshes[i]->buffer)[0]), iconMeshes[i]->buffer->size() * sizeof(float));
		iconMeshes[i]->va->addBuffer(*temp, cubeLayout);
	}
}

void UiRenderer::renderElement(UiElement& element) {
	renderer.drawUi(quadMesh, Ui, element.position, element.size, glm::vec3(0), element.texture);
}

void UiRenderer::renderCube() {
	for (size_t i = 0; i < 9; i++) {
		renderer.drawIcon(*iconMeshes[i]->va, cubeShader, glm::vec2(((896 - (9 * 40)) / 2 + 30) + 37 * i, 30.0f), glm::vec2(20.0f, 20.0f));
	}

}
