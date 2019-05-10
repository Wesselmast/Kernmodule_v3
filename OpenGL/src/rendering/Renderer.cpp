#include "Renderer.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>


bool terrainBound = true;

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

Renderer::Renderer(glm::mat4& proj, glm::mat4* view, glm::mat4& uiProj, int& screenHeight, int& screenWith) : sh("res/shaders/Sprite.shader"), terrain("res/textures/CANDEMAN.png"), proj(proj), uiProj(uiProj), screenHeight(screenHeight), screenWith(screenWith) {
	sh.bind();
	terrain.bind();
	this->proj = proj;
	this->view = view;
}

Renderer::~Renderer() {
	sh.bind();
}

void Renderer::draw(const VertexArray & va, const IndexBuffer & ib, Shader & shader, glm::mat4 modelTransform) {
	glm::mat4 mvp = proj * (*view) * modelTransform;
	shader.bind();
	shader.setUniformMat4f("u_MVP", mvp);
	va.bind();
	ib.bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(const VertexArray & va, Shader& shader, glm::mat4 modelTransform) {
	glm::mat4 mvp = proj * (*view) * modelTransform;

	shader.bind();
	shader.setUniformMat4f("u_MVP", mvp);

	va.bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::draw(const VertexArray & va, Shader& shader, glm::mat4 modelTransform, unsigned int amountOfVerts) {
	glm::mat4 mvp = proj * (*view) * modelTransform;

	if (!terrainBound) shader.bind();

	shader.setUniformMat4f("u_MVP", mvp);

	va.bind();
	glDrawArrays(GL_TRIANGLES, 0, amountOfVerts);
	terrainBound = true;
}

void Renderer::draw(ChunkMesh* mesh) {
	if (!terrainBound)
		terrain.bind();

	draw(*(mesh->va), sh, glm::mat4(1), mesh->buffer->size() / 8);
}

void Renderer::drawUi(VertexArray& va, Shader& ui, glm::vec2 Pos, glm::vec2 Size, glm::vec3 rot, Texture& tex) {
	tex.bind();
	glm::mat4 transform(1.0f);

	transform = glm::translate(transform, glm::vec3((Pos.x - Size.x / 2), (Pos.y - Size.y / 2), -300.0f));
	transform = glm::scale(transform, glm::vec3(Size.x, Size.y, 1.0f));

	glm::mat4 mvp = glm::scale(glm::mat4(1.0f), glm::vec3(((float)screenHeight * 896) / ((float)screenWith * 504), 1.0f, 1.0f)) * uiProj * transform;
	ui.bind();
	ui.setUniformMat4f("u_MP", mvp);

	va.bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);

	terrainBound = false;
}

void Renderer::drawIcon(VertexArray& va, Shader& ui, glm::vec2 pos, glm::vec2 size) {
	terrain.bind();
	glm::mat4 transform(1.0f);

	transform = glm::translate(transform, glm::vec3((pos.x - size.x / 2), (pos.y - size.y / 2), -250.0f));
	transform = glm::rotate(transform, (float)45 * 0.0174532925f, glm::vec3(1.0f, 1.5f, 0.4f));
	transform = glm::scale(transform, glm::vec3(size.x, size.y, size.x));

	glm::mat4 mvp = glm::scale(glm::mat4(1.0f), glm::vec3(((float)screenHeight * 896) / ((float)screenWith * 504), 1.0f, 1.0f)) * uiProj * transform;
	ui.bind();
	ui.setUniformMat4f("u_MP", mvp);

	va.bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);

	terrainBound = true;
}