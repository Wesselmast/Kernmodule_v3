#include "Renderer.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>



float quad[] = {
	 0,	0,	0, 0,
	 0,	1,	1, 0,
	 1,	1,	1, 1,
	 1,	1,	1, 1,
	 1,	0,	0, 1,
	 0,	0,	0, 0,
	};

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL] (" << error << ")" << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}


Renderer::Renderer(glm::mat4& proj, glm::mat4* view, glm::mat4& uiProj, int& screenHeight, int& screenWith) : sh("res/shaders/Sprite.shader"), terrain("res/textures/CANDEMAN.png"), ui("res/shaders/Ui.shader"), proj(proj), uiProj(uiProj), screenHeight(screenHeight),screenWith(screenWith)
{
	sh.Bind();
	terrain.Bind();
	this->proj = proj;
	this->view = view;

	static VertexBuffer vb(quad, 6 * 4 * sizeof(float));
	static VertexBufferLayout lay;
	lay.Push<float>(2);
	lay.Push<float>(2);
	
	quadMesh.AddBuffer(vb, lay);
}

Renderer::~Renderer()
{
	sh.Bind();
}


void Renderer::Draw(const VertexArray & va, const IndexBuffer & ib, Shader & shader, glm::mat4 modelTransform)
{
	glm::mat4 mvp = proj * (*view) * modelTransform;
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", mvp);
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const VertexArray & va, Shader& shader, glm::mat4 modelTransform)
{
	glm::mat4 mvp = proj * (*view) * modelTransform;
	
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", mvp);

	va.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::Draw(const VertexArray & va, Shader& shader, glm::mat4 modelTransform, unsigned int amountOfVerts)
{
	glm::mat4 mvp = proj * (*view) * modelTransform;

	shader.Bind();
	shader.SetUniformMat4f("u_MVP", mvp);

	va.Bind();
	glDrawArrays(GL_TRIANGLES, 0, amountOfVerts);
}

void Renderer::Draw(ChunkMesh* mesh)
{
	Draw(*(mesh->va), sh, glm::mat4(1), mesh->buffer->size() / 8);
}

void Renderer::DrawUi(glm::vec2 Pos, glm::vec2 Size)
{

	glm::mat4 transform(1.0f);
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(Pos.x, Pos.y, 0.0f));
	transform *= glm::scale(glm::mat4(1.0f), glm::vec3(Size.x, Size.y, 0.0f));
	
	

	glm::mat4 mvp = glm::scale(glm::mat4(1.0f), glm::vec3(((float)screenHeight * 854)/((float)screenWith * 480), 1.0f, 1.0f)) * uiProj * transform;
	ui.Bind();
	ui.SetUniformMat4f("u_MP", mvp);
	quadMesh.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
