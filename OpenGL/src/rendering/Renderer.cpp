#include "Renderer.h"
#include <iostream>

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

Renderer::Renderer(const glm::mat4& proj, glm::mat4* view) : sh("res/shaders/Sprite.shader"), terrain("res/textures/terrain.png")
{
	sh.Bind();
	terrain.Bind();
	this->proj = proj;
	this->view = view;
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
	Draw(*(mesh->va), sh, glm::mat4(1), mesh->buffer->size());
}
